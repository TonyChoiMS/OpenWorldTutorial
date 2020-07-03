// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ObjectWithinPool.h"
#include "ObjectPool.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnObjects.generated.h"

class UBoxComponent;

UCLASS()
class OPENWORLDTUTORIAL_API ASpawnObjects : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnObjects();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	float GetLifeSpan();
	class UBoxComponent* SpawnVolume;

	UPROPERTY(EditAnywhere, Category="Spawner")
	UObjectPool* ObjectPooler;

	UPROPERTY(EditAnywhere, Category = "Trigger")
	bool trigger;

	UPROPERTY(EditAnywhere, Category = "Spawner")
	float LifeSpan = 5.0f;

	UPROPERTY(EditAnywhere, Category = "Spawner")
	float SpawnCooldown = 0.1f;

	FTimerHandle SpawnCooldownTimer;

	void Spawn();
};
