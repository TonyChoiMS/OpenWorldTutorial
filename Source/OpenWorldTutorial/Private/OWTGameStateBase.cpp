// Fill out your copyright notice in the Description page of Project Settings.


#include "OWTGameStateBase.h"

AOWTGameStateBase::AOWTGameStateBase()
{
	TotalGameScore = 0;
	bGameCleared = false;
}

int32 AOWTGameStateBase::GetTotalGameScore() const
{
	return TotalGameScore;
}

void AOWTGameStateBase::AddGameScore()
{
	TotalGameScore++;
}

void AOWTGameStateBase::SetGameCleared()
{
	bGameCleared = true;
}

bool AOWTGameStateBase::IsGameCleared() const
{
	return bGameCleared;
}
