// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "OpenWorldTutorial.h"
#include "Blueprint/UserWidget.h"
#include "HUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class OPENWORLDTUTORIAL_API UHUDWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void BindCharacterStat(class UCharacterStatComponent* CharacterStat);
	void BindPlayerState(class AOWTPlayerState* PlayerState);

protected:
	virtual void NativeConstruct() override;
	void UpdateCharacterStat();
	void UpdatePlayerState();

private:
	TWeakObjectPtr<class UCharacterStatComponent> CurrentCharacterStat;
	TWeakObjectPtr<class AOWTPlayerState> CurrentPlayerState;

	UPROPERTY()
	class UProgressBar* HPBar;	

	UPROPERTY()
	class UProgressBar* ExpBar;

	UPROPERTY()
	class UTextBlock* PlayerName;

	UPROPERTY()
	class UTextBlock* PlayerLevel;

	UPROPERTY()
	class UTextBlock* CurrentScore;

	UPROPERTY()
	class UTextBlock* HighScore;
};
