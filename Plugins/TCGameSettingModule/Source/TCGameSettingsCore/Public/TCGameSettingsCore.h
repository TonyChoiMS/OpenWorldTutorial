#pragma once

#include "Modules/ModuleManager.h"

class TCGameSettingsCore : public IModuleInterface
{
public:

protected:
	// IModuleInterface implementation
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};