
#include "TCGameSettingsPlayer.h"
#include "GameFramework/PlayerController.h"
#include "Engine/LocalPlayer.h"
#include "Misc/TCGameSettingsInputLogs.h"

FString ITCGameSettingsPlayer::GetUniquePlayerIdentifier(const APlayerController* PlayerController)
{
	check(PlayerController);
	return PlayerController->Implements<UTCGameSettingsPlayer>() ? Execute_GetUniquePlayerIdentifier(PlayerController) : GetUniquePlayerIdentifier_Default(PlayerController);
}

FString ITCGameSettingsPlayer::GetUniquePlayerIdentifier_Default(const APlayerController* PlayerController)
{
	check(PlayerController);
	check(PlayerController->GetLocalPlayer());
	return FString::FromInt(PlayerController->GetLocalPlayer()->GetControllerId());
}

FString ITCGameSettingsPlayer::GetUniquePlayerIdentifier_Implementation() const
{
	const APlayerController* ThisPC = Cast<APlayerController>(this);
	return ThisPC ? GetUniquePlayerIdentifier_Default(ThisPC) : FString();
}

FInputMappingPreset ITCGameSettingsPlayer::GetDefaultInputMappingPreset(const APlayerController* PlayerController)
{
	check(PlayerController);
	return PlayerController->Implements<UTCGameSettingsPlayer>() ? Execute_GetDefaultInputMappingPreset(PlayerController) : GetDefaultInputMappingPreset_Default();
}

FInputMappingPreset ITCGameSettingsPlayer::GetDefaultInputMappingPreset_Default()
{
	return UInputMappingManager::GetDefaultInputPresets()[0];
}

FInputMappingPreset ITCGameSettingsPlayer::GetDefaultInputMappingPreset_Implementation() const
{
	return GetDefaultInputMappingPreset_Default();
}

bool ITCGameSettingsPlayer::GetInputMappings(const APlayerController* PlayerController, FPlayerInputMappings& InputMappings)
{
	check(PlayerController);
	return PlayerController->Implements<UTCGameSettingsPlayer>() ? Execute_GetInputMappings(PlayerController, InputMappings) : false;
}

bool ITCGameSettingsPlayer::GetInputMappings_Implementation(FPlayerInputMappings& InputMappings) const
{
	return false;
}

void ITCGameSettingsPlayer::SaveInputMappings(APlayerController* PlayerController, FPlayerInputMappings InputMappings)
{
	check(PlayerController);
	if (PlayerController->Implements<UTCGameSettingsPlayer>())
	{
		UE_LOG(LogTCGameSettingsInput, Log, TEXT("%s implements ITCGameSettingsPlayer, calling SaveInputMappings"), *PlayerController->GetName());
		Execute_SaveInputMappings(PlayerController, InputMappings);
	}
}

void ITCGameSettingsPlayer::SaveInputMappings_Implementation(FPlayerInputMappings InputMappings)
{

}
