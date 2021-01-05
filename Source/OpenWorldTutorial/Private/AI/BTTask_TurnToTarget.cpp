// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_TurnToTarget.h"
#include "MonsterAIController.h"
#include "MyCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_TurnToTarget::UBTTask_TurnToTarget()
{
	NodeName = TEXT("Turn");
}

EBTNodeResult::Type UBTTask_TurnToTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto MyCharacter = Cast<AMyCharacter>(OwnerComp.GetAIOwner()->GetPawn());

	if (nullptr == MyCharacter)
	{
		return EBTNodeResult::Failed;
	}

	auto Target = Cast<AMyCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AMonsterAIController::TargetKey));
	if (nullptr == Target)
	{
		return EBTNodeResult::Failed;
	}

	FVector LookVector = Target->GetActorLocation() - MyCharacter->GetActorLocation();
	LookVector.Z = 0.0f;
	FRotator TargetRot = FRotationMatrix::MakeFromX(LookVector).Rotator();
	MyCharacter->SetActorRotation(FMath::RInterpTo(MyCharacter->GetActorRotation(), TargetRot, GetWorld()->GetDeltaSeconds(), 2.0f));
		
	return EBTNodeResult::Succeeded;
}
