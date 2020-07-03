// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectPool.h"
#include  "UObject/ConstructorHelpers.h"
#include "GameFramework/Actor.h"
#include "Engine.h"

// Sets default values for this component's properties
UObjectPool::UObjectPool()
{
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UObjectPool::BeginPlay()
{
	Super::BeginPlay();

	if (PooledObjectSubclass != NULL)
	{
		UWorld* const World = GetWorld();
		if (World)
		{
			for (int i = 0; i < PoolSize; i++)
			{
				AObjectWithinPool* PoolableActor = GetWorld()->SpawnActor < AObjectWithinPool>(PooledObjectSubclass, FVector().ZeroVector, FRotator().ZeroRotator);
				PoolableActor->SetActive(false);
				Pool.Add(PoolableActor);
				UE_LOG(LogTemp, Warning, TEXT("Added Object to the pool"));
			}
		}
	}
}

AObjectWithinPool * UObjectPool::GetPooledObject()
{
	for (AObjectWithinPool* PoolableActor : Pool)
	{
		if (!PoolableActor->IsActive())
			return PoolableActor;
	}
	return nullptr;
}

// Called every frame
void UObjectPool::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

