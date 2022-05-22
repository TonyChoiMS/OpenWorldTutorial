
#include "Misc/SettingOptionFactory.h"
#include "TCGameSettingsLogs.h"


TArray<FSettingOption> USettingOptionFactory::ConstructOptions_Implementation() const
{
	UE_LOG(LogTCGameSettings, Error, TEXT("Default ConstructOptions called, no options constructed"));
	return TArray<FSettingOption>();
}
