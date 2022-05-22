// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Modules/ModuleManager.h"

class FTCGameSettingModule : public IModuleInterface
{
public:
	// static get module
	static inline FTCGameSettingModule* Get()
	{
		return FModuleManager::LoadModulePtr<FTCGameSettingModule>("TCGameSettings");
	}

protected:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
