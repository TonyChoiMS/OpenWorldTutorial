// Fill out your copyright notice in the Description page of Project Settings.


#include "OWTGameStateBase.h"

AOWTGameStateBase::AOWTGameStateBase()
{
	TotalGameScore = 0;
}

int32 AOWTGameStateBase::GetTotalGameScore() const
{
	return TotalGameScore;
}

void AOWTGameStateBase::AddGameScore()
{
	TotalGameScore++;
}
