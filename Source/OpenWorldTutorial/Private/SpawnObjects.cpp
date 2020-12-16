// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnObjects.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"

// Sets default values
ASpawnObjects::ASpawnObjects()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SpawnVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnVolume"));
	RootComponent = SpawnVolume;

	ObjectPooler = CreateDefaultSubobject<UObjectPool>(TEXT("ObjectPooler"));
}

// Called when the game starts or when spawned
void ASpawnObjects::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(SpawnCooldownTimer, this, &ASpawnObjects::Spawn, SpawnCooldown, false);
}

void ASpawnObjects::Tick(float DeltaTime)
{
}

void ASpawnObjects::Spawn()
{
	ACharacter* myCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	AObjectWithinPool* PoolableActor = ObjectPooler->GetPooledObject();
	if (PoolableActor == nullptr)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Cannot Spawn"));
		GetWorldTimerManager().SetTimer(SpawnCooldownTimer, this, &ASpawnObjects::Spawn, SpawnCooldown, false);
		return;
	}

	PoolableActor->SetActorLocation(myCharacter->GetNavAgentLocation());
	PoolableActor->SetLifeSpan(LifeSpan);
	PoolableActor->SetActive(true);
	PoolableActor->SetActorRotation(myCharacter->GetActorRotation());
	GetWorldTimerManager().SetTimer(SpawnCooldownTimer, this, &ASpawnObjects::Spawn, SpawnCooldown, false);
	//UE_LOG(LogTemp, Warning, TEXT("Spawning"));
}

