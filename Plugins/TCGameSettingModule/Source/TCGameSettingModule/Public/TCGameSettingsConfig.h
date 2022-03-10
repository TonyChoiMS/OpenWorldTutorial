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

	// Setting�� ������ Config ini���� �̸� (extension ����)
	// ���� ���� ���� �����ؾ��մϴ�.
	UPROPERTY(Config, EditAnywhere, Category = Settings)
	FString SettingsIniName = "Settings";

	// Config ini ���Ͽ��� ���� Config section �̸�
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
