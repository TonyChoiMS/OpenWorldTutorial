// Fill out your copyright notice in the Description page of Project Settings.


#include "OWTPlayerState.h"
#include "OpenWorldGameInstance.h"

AOWTPlayerState::AOWTPlayerState()
{
	CharacterLevel = 1;
	GameScore = 0;
	Exp = 0;
}

int32 AOWTPlayerState::GetGameScore() const
{
	return GameScore;
}

int32 AOWTPlayerState::GetCharacterLevel() const
{
	return CharacterLevel;
}

float AOWTPlayerState::GetExpRatio() const
{
	if (CurrentStatData->NextExp <= KINDA_SMALL_NUMBER)
		return 0.0f;

	float Result = (float)Exp / (float)CurrentStatData->NextExp;
	ABLOG(Warning, TEXT("Ratio : %f, Current : %d, Next : %d"), Result, Exp, CurrentStatData->NextExp);
	return Result;
}

bool AOWTPlayerState::AddExp(int32 IncomeExp)
{
	if (CurrentStatData->NextExp == -1)
		return false;

	bool DidLevelUp = false;
	Exp += IncomeExp;
	if (Exp >= CurrentStatData->NextExp)
	{
		Exp -= CurrentStatData->NextExp;
		SetCharacterLevel(CharacterLevel + 1);
		DidLevelUp = true;
	}

	OnPlayerStateChanged.Broadcast();
	return DidLevelUp;
}

void AOWTPlayerState::AddGameScore()
{
	GameScore++;
	OnPlayerStateChanged.Broadcast();
}

void AOWTPlayerState::InitPlayerData()
{
	SetPlayerName(TEXT("Destiny"));
	SetCharacterLevel(5);
	GameScore = 0;
	Exp = 0;
}

void AOWTPlayerState::SetCharacterLevel(int32 NewCharacterLevel)
{
	auto OpenWorldGameInstance = Cast<UOpenWorldGameInstance>(GetGameInstance());
	ABCHECK(nullptr != OpenWorldGameInstance);

	CurrentStatData = OpenWorldGameInstance->GetABCharacterData(NewCharacterLevel);
	ABCHECK(nullptr != CurrentStatData);

	CharacterLevel = NewCharacterLevel;
}

