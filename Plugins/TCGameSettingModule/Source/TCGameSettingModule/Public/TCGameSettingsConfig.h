// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/DeveloperSettings.h"
#include "TCGameSettingsConfig.generated.h"

/**
 * 
 */
UCLASS(config=Game, defaultconfig)
class TCGAMESETTINGMODULE_API UTCGameSettingsConfig : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UTCGameSettingsConfig();

	// Setting을 저장할 Config ini파일 이름 (extension 제외)
	// 엔진 시작 전에 지정해야합니다.
	UPROPERTY(Config, EditAnywhere, Category = Settings)
	FString SettingsIniName = "Settings";

	// Config ini 파일에서 사용될 Config section 이름
	UPROPERTY(Config, EditAnywhere, Category = Settings)
	FString SettingsSectionName = "Settings";

protected:
	virtual void PostInitProperties() override;

#if WITH_EDITOR
	virtual FText GetSectionText() const override;
	virtual FText GetSectionDescription() const override;
#endif

private:
	
};
