// Fill out your copyright notice in the Description page of Project Settings.


#include "OpenWorldGameMode.h"
#include "TimerManager.h"

AOpenWorldGameMode::AOpenWorldGameMode()
{
	TimerBetweenWaves = 2.0f;
}

void AOpenWorldGameMode::StartWave()
{
	WaveCount++;

	NrOfBotsToSpawn = 2 * WaveCount;

	GetWorldTimerManager().SetTimer(TimerHandle_BotSpawner, this, &AOpenWorldGameMode::SpawnBotTimerElapsed, 1.0f, true, 0.0f);
}


void AOpenWorldGameMode::EndWave()
{
	GetWorldTimerManager().ClearTimer(TimerHandle_BotSpawner);

	PrepareForNextWave();
}

void AOpenWorldGameMode::PrepareForNextWave()
{
	FTimerHandle TimerHandle_NextWaveStart;
	GetWorldTimerManager().SetTimer(TimerHandle_NextWaveStart, this, &AOpenWorldGameMode::StartWave, TimerBetweenWaves, false);
}

void AOpenWorldGameMode::StartPlay()
{
	Super::StartPlay();

	PrepareForNextWave();
}

void AOpenWorldGameMode::SpawnBotTimerElapsed()
{
	SpawnNewBot();

	NrOfBotsToSpawn--;

	if (NrOfBotsToSpawn <= 0)
	{
		EndWave();
	}
}
