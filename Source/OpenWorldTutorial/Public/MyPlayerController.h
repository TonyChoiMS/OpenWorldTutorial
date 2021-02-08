// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "OpenWorldTutorial.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class OPENWORLDTUTORIAL_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AMyPlayerController();

	virtual void PostInitializeComponents() override;
	//virtual void Possess(APawn* InPawn) override;

	class UHUDWidget* GetHUDWidget() const;
	void NPCKill(class AMyCharacter* KilledNPC) const;
	void AddGameScore() const;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
	TSubclassOf<class UHUDWidget> HUDWidgetClass;

private:
	UPROPERTY()
	class UHUDWidget* HUDWidget;

	UPROPERTY()
	class AOWTPlayerState* OWTPlayerState;

};
