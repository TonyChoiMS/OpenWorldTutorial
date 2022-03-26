#include "TCGameSettingsCore.h"

#if WITH_EDITOR
#include "ISettingsModule.h"
#endif

#define LOCTEXT_NAMESPACE "TCGameSettingsCore"

void TCGameSettingsCore::StartupModule()
{
	
}

void TCGameSettingsCore::ShutdownModule()
{

}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_GAME_MODULE(FDefaultGameModuleImpl, TCGameSettingsCore)