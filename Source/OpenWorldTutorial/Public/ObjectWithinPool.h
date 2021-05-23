// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ObjectWithinPool.generated.h"

UCLASS()
class OPENWORLDTUTORIAL_API AObjectWithinPool : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AObjectWithinPool();

	// Actor 클래스 함수 오버라이드.
	// InLifespan 시간이 되면 Actor를 Destroy, InLifespan을 0으로 세팅할 경우 타이머 클리어
	virtual void SetLifeSpan(float InLifespan) override;

	// 오브젝트 활성/비활성화 할 함수
	void SetActive(bool InActive);

	// 오브젝트 활성화 상태를 체크하는 함수
	bool IsActive();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	float LifeSpan = 2.0f;

	// 오브젝트를 비활성화 시킬 타이머
	FTimerHandle LifespanTimer;
	// 활성상태
	bool Active;
	// 비활성화 시킬 함수
	void Deactivate();
};
