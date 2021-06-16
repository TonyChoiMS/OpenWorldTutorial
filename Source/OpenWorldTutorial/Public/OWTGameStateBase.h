// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "OpenWorldTutorial.h"
#include "GameFramework/GameStateBase.h"
#include "OWTGameStateBase.generated.h"

/**
 * 
 */
UCLASS()
class OPENWORLDTUTORIAL_API AOWTGameStateBase : public AGameStateBase
{
	GENERATED_BODY()

public:
	AOWTGameStateBase();

public:
	int32 GetTotalGameScore() const;
	void AddGameScore();
	void SetGameCleared();
	bool IsGameCleared() const;

private:
	UPROPERTY(Transient)
	int32 TotalGameScore;

	UPROPERTY(Transient)
	bool bGameCleared;
};
