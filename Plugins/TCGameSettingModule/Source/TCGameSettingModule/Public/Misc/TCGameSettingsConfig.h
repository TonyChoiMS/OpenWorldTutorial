#pragma once

#include "Engine/DeveloperSettings.h"
#include "TCGameSettingsConfig.generated.h"

// Plugin configuration page in Project Settings
UCLASS(config=Game, defaultconfig)
class TCGAMESETTINGMODULE_API UTCGameSettingsConfig : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UTCGameSettingsConfig();

	// Config ini file (without extension) that settings are saved to.
	// Requires engine restart for changes to take effect.
	UPROPERTY(Config, EditAnywhere, Category = Settings)
	FString SettingsIniName = "Settings";

	// Config section that settings are saved to within the config ini file
	UPROPERTY(Config, EditAnywhere, Category = Settings)
	FString SettingsSectionName = "Settings";

protected:
	virtual void PostInitProperties() override;

#if WITH_EDITOR
	virtual FText GetSectionText() const override;
	virtual FText GetSectionDescription() const override;
#endif


};