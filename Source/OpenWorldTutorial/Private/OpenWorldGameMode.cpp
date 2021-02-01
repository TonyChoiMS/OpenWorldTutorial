// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenWorldGameMode.h"
#include "SHealthComponent.h"
#include "SGameState.h"
#include "SPlayerState.h"
#include "TimerManager.h"
#include "MyCharacter.h"
#include "OWTPlayerState.h"

AOpenWorldGameMode::AOpenWorldGameMode()
{
	TimerBetweenWaves = 2.0f;

	GameStateClass = ASGameState::StaticClass();
	//PlayerStateClass = APlayerState::StaticClass();
	PlayerStateClass = AOWTPlayerState::StaticClass();

	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickInterval = 1.0f;

	/*static ConstructorHelpers::FClassFinder<APawn> BP_PAWN_C(TEXT("/Game/Character/Human/BP_MyCharacter"));
	if (BP_PAWN_C.Succeeded())
	{
		DefaultPawnClass = BP_PAWN_C.Class;
	}*/
}

void AOpenWorldGameMode::StartWave()
{
	WaveCount++;

	NrOfBotsToSpawn = 2 * WaveCount;

	GetWorldTimerManager().SetTimer(TimerHandle_BotSpawner, this, &AOpenWorldGameMode::SpawnBotTimerElapsed, 1.0f, true, 0.0f);

	SetWaveState(EWaveState::WaveInProgress);
}


void AOpenWorldGameMode::EndWave()
{
	GetWorldTimerManager().ClearTimer(TimerHandle_BotSpawner);

	SetWaveState(EWaveState::WaitingToComplete);
}

void AOpenWorldGameMode::PrepareForNextWave()
{
	GetWorldTimerManager().SetTimer(TimerHandle_NextWaveStart, this, &AOpenWorldGameMode::StartWave, TimerBetweenWaves, false);

	SetWaveState(EWaveState::WaitingToStart);

	RestartDeadPlayers();
}

void AOpenWorldGameMode::CheckWaveState()
{
	bool bIsPreparingForWave = GetWorldTimerManager().IsTimerActive(TimerHandle_NextWaveStart);

	if (NrOfBotsToSpawn > 0 || bIsPreparingForWave)
	{
		return;
	}

	bool bIsAnyBotAlive = false;

	for (FConstPawnIterator It = GetWorld()->GetPawnIterator(); It; ++It)
	{
		APawn* TestPawn = It->Get();
		if (TestPawn == nullptr || TestPawn->IsPlayerControlled())
		{
			continue;
		}

		USHealthComponent* HealthComp = Cast<USHealthComponent>(TestPawn->GetComponentByClass(USHealthComponent::StaticClass()));
		if (HealthComp && HealthComp->GetHealth() > 0.0f)
		{
			bIsAnyBotAlive = true;
			break;
		}
	}
	
	if (!bIsAnyBotAlive)
	{
		SetWaveState(EWaveState::WaveComplete);

		PrepareForNextWave();
	}
}

void AOpenWorldGameMode::CheckAnyPlayerAlive()
{
	for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
	{
		APlayerController* PC = It->Get();
		if (PC && PC->GetPawn())
		{
			APawn* MyPawn = PC->GetPawn();
			USHealthComponent* HealthComp = Cast<USHealthComponent>(MyPawn->GetComponentByClass(USHealthComponent::StaticClass()));
			if (ensure(HealthComp) && HealthComp->GetHealth() > 0.0f)
			{
				// A Player is still alive
				return;
			}
		}
	}
	
	// NoPlayer alive
	GameOver();
}

void AOpenWorldGameMode::GameOver()
{
	EndWave();

	// @TODO :: Finish up the match, present 'game over' to players.

	SetWaveState(EWaveState::GameOver);

	UE_LOG(LogTemp, Log, TEXT("Game Over! Players Died"));
}

void AOpenWorldGameMode::SetWaveState(EWaveState NewState)
{
	ASGameState* GS = GetGameState<ASGameState>();

	if (ensureAlways(GS))
	{
		GS->SetWaveState(NewState);
	}
}

void AOpenWorldGameMode::RestartDeadPlayers()
{
	for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
	{
		APlayerController* PC = It->Get();
		if (PC && PC->GetPawn() == nullptr)
		{
			RestartPlayer(PC);
		}
	}
}

void AOpenWorldGameMode::StartPlay()
{
	Super::StartPlay();

	PrepareForNextWave();
}

void AOpenWorldGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	CheckWaveState();

	CheckAnyPlayerAlive();
}

void AOpenWorldGameMode::PostLogin(APlayerController * NewPlayer)
{
	Super::PostLogin(NewPlayer);

	auto OWTPlayerState = Cast<AOWTPlayerState>(NewPlayer->PlayerState);
	ABCHECK(nullptr != OWTPlayerState);
	OWTPlayerState->InitPlayerData();
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
