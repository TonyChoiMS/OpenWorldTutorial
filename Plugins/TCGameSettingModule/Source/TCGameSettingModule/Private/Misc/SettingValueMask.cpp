#include "Misc/SettingValueMask.h"
#include "TCGameSettingsLogs.h"

FString USettingValueMask::MaskValue_Implementation(const FString& ConsoleValue) const
{
	UE_LOG(LogTCGameSettings, Error, TEXT("Undefined setting mask applied"));
	return ConsoleValue;
}

FString USettingValueMask::RecombineValues_Implementation(const FString& SettingValue, const FString& ConsoleValue) const
{
	UE_LOG(LogTCGameSettings, Error, TEXT("Undefined setting mask applied"));
	return SettingValue;
}
