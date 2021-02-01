// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "OpenWorldTutorial.h"
#include "GameFramework/PlayerState.h"
#include "OWTPlayerState.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnPlayerStateChangedDelegate);

/**
 * 
 */
UCLASS()
class OPENWORLDTUTORIAL_API AOWTPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	AOWTPlayerState();

	int32 GetGameScore() const;
	int32 GetCharacterLevel() const;

	void InitPlayerData();

	FOnPlayerStateChangedDelegate OnPlayerStateChanged;

protected:
	UPROPERTY(Transient)
	int32 GameScore;

	UPROPERTY(Transient)
	int32 CharacterLevel;
};
