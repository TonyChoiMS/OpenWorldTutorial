// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GamePlayWidget.h"
#include "GamePlayResultWidget.generated.h"

/**
 * 
 */
UCLASS()
class UGamePlayResultWidget : public UGamePlayWidget
{
	GENERATED_BODY()
	
public:
	void BindGameState(class AOWTGameStateBase* GameState);
	
protected:
	virtual void NativeConstruct() override;

private:
	TWeakObjectPtr<class AOWTGameStateBase> CurrentGameState;
};
