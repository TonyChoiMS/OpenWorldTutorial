// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/PawnMovementComponent.h"

UMyAnimInstance::UMyAnimInstance()
{
	CurrentPawnSpeed = 0.0f;
	bIsInAir = false;
}

void UMyAnimInstance::NativeUpdateAnimation(float DeltaSecond)
{
	Super::NativeUpdateAnimation(DeltaSecond);

	auto Pawn = TryGetPawnOwner();
	if (::IsValid(Pawn))
	{
		CurrentPawnSpeed = Pawn->GetVelocity().Size();
		auto Character = Cast<ACharacter>(Pawn);
		if (Character)
		{
			bIsInAir = Character->GetMovementComponent()->IsFalling();
		}
	}
}
