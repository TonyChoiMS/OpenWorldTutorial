
#include "TCGameSettingsInput.h"
#include "InputMappingManager.h"
//#include "Misc/CoreDelegates.h"
//#include "Misc/TCGameSettingsInputLogs.h"

#if WITH_EDITOR
#include "ISettingsModule.h"
#endif

#define LOCTEXT_NAMESPACE "FTCGAmeSettingsModule"

void FTCGameSettingsInputModule::StartupModule()
{
	UE_LOG(LogTCGameSettingsInput, Log, TEXT("TCGAmeSettingsInput module starting up"));

	FCoreDelegates::OnPostEngineInit.AddLambda([]()
	{
		//UInputMappingManager::Get();
	});
}

void FTCGameSettingsInputModule::ShutdownModule()
{

}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FTCGameSettingsInputModule, TCGameSettingsInput)
