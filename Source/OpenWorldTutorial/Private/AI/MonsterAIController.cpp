// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

const FName AMonsterAIController::HomePosKey(TEXT("HomePos"));
const FName AMonsterAIController::PatrolPosKey(TEXT("PatrolPos"));
const FName AMonsterAIController::TargetKey(TEXT("Target"));

AMonsterAIController::AMonsterAIController()
{
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBObject(TEXT("/Game/BP/AdvancedAI/BB_AdvancedAI.BB_AdvancedAI"));
	if (BBObject.Succeeded())
	{
		BBAsset = BBObject.Object;
	}

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject(TEXT("/Game/BP/AdvancedAI/BT_AdvancedAI.BT_AdvancedAI"));

	if (BTObject.Succeeded())
	{
		BTAsset = BTObject.Object;
	}
}

void AMonsterAIController::OnPossess(APawn * InPawn)
{
	Super::OnPossess(InPawn);
	
	if (UseBlackboard(BBAsset, Blackboard))
	{
		Blackboard->SetValueAsVector(HomePosKey, InPawn->GetActorLocation());
		if (!RunBehaviorTree(BTAsset))
		{
			ABLOG(Error, TEXT("AIController couldn't run behavior tree!"));
		}
	}
}