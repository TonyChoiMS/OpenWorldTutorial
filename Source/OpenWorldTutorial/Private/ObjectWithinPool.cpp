// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectWithinPool.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
AObjectWithinPool::AObjectWithinPool()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SetActorEnableCollision(false);
}

void AObjectWithinPool::SetLifeSpan(float InLifespan)
{
	LifeSpan = InLifespan;
	GetWorldTimerManager().SetTimer(LifespanTimer, this, &AObjectWithinPool::Deactivate, LifeSpan, false);
}

void AObjectWithinPool::SetActive(bool InActive)
{
	Active = InActive;
	SetActorHiddenInGame(!InActive);
}

bool AObjectWithinPool::IsActive()
{
	return Active;
}

// Called when the game starts or when spawned
void AObjectWithinPool::BeginPlay()
{
	Super::BeginPlay();
	
}

void AObjectWithinPool::Deactivate()
{
	SetActive(false);
}

