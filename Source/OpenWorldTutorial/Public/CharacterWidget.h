// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "OpenWorldTutorial.h"
#include "Blueprint/UserWidget.h"
#include "CharacterWidget.generated.h"

/**
 * 
 */
UCLASS()
class OPENWORLDTUTORIAL_API UCharacterWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void BindCharacterStat(class UCharacterStatComponent* NewCharacterStat);

protected:
	virtual void NativeConstruct() override;
	void UpdateHPWidget();

private:
	// WeakPtr를 사용해보기 위해 선언.
	TWeakObjectPtr<class UCharacterStatComponent> CurrentCharacterStat;

	UPROPERTY()
	class UProgressBar* HPPProgressBar;
};
