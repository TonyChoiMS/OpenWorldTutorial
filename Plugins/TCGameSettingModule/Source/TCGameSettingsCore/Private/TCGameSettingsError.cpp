// Fill out your copyright notice in the Description page of Project Settings.


#include "TCGameSettingsError.h"
#include "Logging/MessageLog.h"
#include "TCGameSettingsLogs.h"
#include "UObject/Class.h"

void TCGameSettingsError::LogError(const FString& Message)
{
	// PIE message log
	FMessageLog("PIE").Error(FText::FromString("TCGameSettings: " + Message));
	// Output log
	UE_LOG(LogAutoSettings, Error, TEXT("%s"), *Message);
}

void TCGameSettingsError::LogInvalidClass(const FString& SourceObjectName, const FString& ClassPropertyName)
{
	LogError(FString::Printf(TEXT("%s has an invalid %s. Please update the property to a valid class."), *SourceObjectName, *ClassPropertyName));
}

void TCGameSettingsError::LogInvalidClass(UClass* SourceClass, const FString& ClassPropertyName)
{
	LogInvalidClass(GetSafeClassName(SourceClass), ClassPropertyName);
}

void TCGameSettingsError::LogWIdgetCreationFailed(UClass* SourceClass, const FString& WidgetName)
{
	LogError(FString::Printf(TEXT("%s: Failed to create %s widget"), *GetSafeClassName(SourceClass), *WidgetName));
}

void TCGameSettingsError::LogMissingCVar(const FString& Context, const FName& CVar)
{
	LogError(FString::Printf(TEXT("%s: Missing or unregistered CVar: '%s'. Please ensure the CVar is registered correctly"), *Context, *CVar.ToString()));
}

FString TCGameSettingsError::GetSafeClassName(UClass* Class)
{
	return Class ? Class->GetName() : "None";
}
