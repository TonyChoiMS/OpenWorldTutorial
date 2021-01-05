// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Attack.h"
#include "MonsterAIController.h"
#include "MyCharacter.h"

UBTTask_Attack::UBTTask_Attack()
{
	bNotifyTick = true;
	bIsAttacking = false;
}

EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto MyCharacter = Cast<AMyCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == MyCharacter)
		return EBTNodeResult::Failed;

	MyCharacter->Attack();
	bIsAttacking = true;
	MyCharacter->OnAttackEnd.AddLambda([this]() -> void {
		bIsAttacking = false;
	});

	return EBTNodeResult::InProgress;
}

void UBTTask_Attack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	if (!bIsAttacking)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}
