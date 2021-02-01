// Fill out your copyright notice in the Description page of Project Settings.


#include "OWTPlayerState.h"

AOWTPlayerState::AOWTPlayerState()
{
	CharacterLevel = 1;
	GameScore = 0;
}

int32 AOWTPlayerState::GetGameScore() const
{
	return GameScore;
}

int32 AOWTPlayerState::GetCharacterLevel() const
{
	return CharacterLevel;
}

void AOWTPlayerState::InitPlayerData()
{
	SetPlayerName(TEXT("Destiny"));
	CharacterLevel = 5;
	GameScore = 0;
}

