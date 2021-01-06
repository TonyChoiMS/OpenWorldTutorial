// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ABCharacterSetting.generated.h"

/**
 * 
 */
UCLASS(config=OpenWorldTutorial)
class OPENWORLDTUTORIALSETTING_API UABCharacterSetting : public UObject
{
	GENERATED_BODY()
	
public:
	UABCharacterSetting();

	UPROPERTY(config)
	TArray<FSoftObjectPath> CharacterAssets;
};
