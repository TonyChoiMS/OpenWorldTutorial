// Fill out your copyright notice in the Description page of Project Settings.


#include "OWTPlayerState.h"
#include "OpenWorldGameInstance.h"
#include "OWTSaveGame.h"

AOWTPlayerState::AOWTPlayerState()
{
	CharacterLevel = 1;
	GameScore = 0;
	GameHighScore = 0;
	Exp = 0;
	SaveSlotName = TEXT("Player1");
}

int32 AOWTPlayerState::GetGameScore() const
{
	return GameScore;
}

int32 AOWTPlayerState::GetGameHighScore() const
{
	return GameHighScore;
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
	SavePlayerData();
	return DidLevelUp;
}

void AOWTPlayerState::AddGameScore()
{
	GameScore++;
	if (GameScore >= GameHighScore)
	{
		GameHighScore = GameScore;
	}
	OnPlayerStateChanged.Broadcast();
	SavePlayerData();
}

void AOWTPlayerState::InitPlayerData()
{
	auto OWTSaveGame = Cast<UOWTSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveSlotName, 0));
	if (nullptr == OWTSaveGame)
	{
		OWTSaveGame = GetMutableDefault<UOWTSaveGame>();
	}

	SetPlayerName(OWTSaveGame->PlayerName);
	SetCharacterLevel(OWTSaveGame->Level);
	GameScore = 0;
	GameHighScore = OWTSaveGame->HighScore;
	Exp = OWTSaveGame->Exp;
	SavePlayerData();
}

void AOWTPlayerState::SavePlayerData()
{
	UOWTSaveGame* NewPlayerData = NewObject<UOWTSaveGame>();
	NewPlayerData->PlayerName = GetPlayerName();
	NewPlayerData->Level = CharacterLevel;
	NewPlayerData->Exp = Exp;
	NewPlayerData->HighScore = GameHighScore;

	if (!UGameplayStatics::SaveGameToSlot(NewPlayerData, SaveSlotName, 0))
	{
		ABLOG(Error, TEXT("SaveGame Error!"));
	}
}

void AOWTPlayerState::SetCharacterLevel(int32 NewCharacterLevel)
{
	auto OpenWorldGameInstance = Cast<UOpenWorldGameInstance>(GetGameInstance());
	ABCHECK(nullptr != OpenWorldGameInstance);

	CurrentStatData = OpenWorldGameInstance->GetABCharacterData(NewCharacterLevel);
	ABCHECK(nullptr != CurrentStatData);

	CharacterLevel = NewCharacterLevel;
}

