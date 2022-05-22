
#include "UI/SettingControls/ToggleSetting.h"
#include "Utility/TCGameSettingsStringUtils.h"

void UToggleSetting::UpdateSelection_Implementation(const FString& Value)
{
	Super::UpdateSelection_Implementation(Value);

	UpdateToggleState(FTCGameSettingsStringUtils::IsTruthy(Value));
}

void UToggleSetting::UpdateToggleState_Implementation(bool State)
{
}

void UToggleSetting::ToggleStateUpdated(bool State)
{
	const int32 IntValue = State ? 1 : 0;

	ApplySettingValue(FString::FromInt(IntValue));
}