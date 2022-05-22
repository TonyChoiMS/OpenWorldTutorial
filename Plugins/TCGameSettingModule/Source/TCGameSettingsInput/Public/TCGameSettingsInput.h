
#pragma  once

#include "Modules/ModuleManager.h"

class FTCGameSettingsInputModule : public IModuleInterface
{
public:
	static inline FTCGameSettingsInputModule* Get()
	{
		return FModuleManager::LoadModulePtr<FTCGameSettingsInputModule>("TCGameSettingsInput");
	}

protected:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};