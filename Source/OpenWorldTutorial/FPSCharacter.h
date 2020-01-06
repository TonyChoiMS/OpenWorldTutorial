// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FPSCharacter.generated.h"

UCLASS()
class OPENWORLDTUTORIAL_API AFPSCharacter : public ACharacter
{
	GENERATED_BODY()

protected:
	// Pawn mesh : 1st person view
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh")
		USkeletalMeshComponent* Mesh1PComponent;

	// Gun Mesh : 1st person view
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh")
		USkeletalMeshComponent* GunMeshComponent;

	// First Person Camera
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Cateogry = "Camera")
		UCameraComponent* CameraComponent;

public:
	AFPSCharacter();

	/*UPROPERTY(EditDefaultsOnly, Cateogry="Projectile")
		TSubclassOf(A)*/

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
