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

	// Actor Ŭ���� �Լ� �������̵�.
	// InLifespan �ð��� �Ǹ� Actor�� Destroy, InLifespan�� 0���� ������ ��� Ÿ�̸� Ŭ����
	virtual void SetLifeSpan(float InLifespan) override;

	// ������Ʈ Ȱ��/��Ȱ��ȭ �� �Լ�
	void SetActive(bool InActive);

	// ������Ʈ Ȱ��ȭ ���¸� üũ�ϴ� �Լ�
	bool IsActive();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	float LifeSpan = 2.0f;

	// ������Ʈ�� ��Ȱ��ȭ ��ų Ÿ�̸�
	FTimerHandle LifespanTimer;
	// Ȱ������
	bool Active;
	// ��Ȱ��ȭ ��ų �Լ�
	void Deactivate();
};
