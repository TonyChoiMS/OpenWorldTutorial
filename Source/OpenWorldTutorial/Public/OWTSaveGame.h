// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "OWTSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class OPENWORLDTUTORIAL_API UOWTSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:
	UOWTSaveGame();

	UPROPERTY()
	int32 Level;

	UPROPERTY()
	int32 Exp;

	UPROPERTY()
	FString PlayerName;

	UPROPERTY()
	int32 HighScore;
};
