// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class TCGAMESETTINGSCORE_API TCGameSettingsError
{
public:
	static void LogError(const FString& Message);

	static void LogInvalidClass(const FString& SourceObjectName, const FString& ClassPropertyName);
	static void LogInvalidClass(UClass* SourceClass, const FString& ClassPropertyName);

	static void LogWIdgetCreationFailed(UClass* SourceClass, const FString& WidgetName);

	static void LogMissingCVar(const FString& Context, const FName& CVar);

private:
	static FString GetSafeClassName(UClass* Class);
};
