// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "OpenWorldTutorial.h"
#include "GameFramework/Actor.h"
#include "ABWeapon.generated.h"

UCLASS()
class OPENWORLDTUTORIAL_API AABWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AABWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(VisibleAnywhere, Category = Weapon)
	USkeletalMeshComponent* Weapon;
};
