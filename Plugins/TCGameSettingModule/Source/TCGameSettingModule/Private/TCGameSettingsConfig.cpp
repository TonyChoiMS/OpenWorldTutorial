// Fill out your copyright notice in the Description page of Project Settings.

#include "TCGameSettingsConfig.h"

#define LOCTEXT_NAMESPACE "FAutoSettingsModule"

UTCGameSettingsConfig::UTCGameSettingsConfig()
{
	CategoryName = "Plugins";
}

void UTCGameSettingsConfig::PostInitProperties()
{
	Super::PostInitProperties();


}

#if WITH_EDITOR
FText UTCGameSettingsConfig::GetSectionText() const
{
	return LOCTEXT("UTCGameSettingsName", "TC GameSettings");
}

FText UTCGameSettingsConfig::GetSectionDescription() const
{
	return LOCTEXT("TCGameSettingDescription", "Configure the Auto Settings plugin.");
}
#endif
#undef LOCTEXT_NAMESPACE

