// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"
#include "HUDWidget.h"
#include "OWTPlayerState.h"
#include "MyCharacter.h"


AMyPlayerController::AMyPlayerController()
{
	static ConstructorHelpers::FClassFinder<UHUDWidget> UI_HUD_C(TEXT("/Game/UI/UI_HUD.UI_HUD_C"));

	if (UI_HUD_C.Succeeded())
	{
		HUDWidgetClass = UI_HUD_C.Class;
	}
}

void AMyPlayerController::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	ABLOG_S(Warning);

}

UHUDWidget * AMyPlayerController::GetHUDWidget() const
{
	return HUDWidget;
}

void AMyPlayerController::NPCKill(AMyCharacter * KilledNPC) const
{
	OWTPlayerState->AddExp(KilledNPC->GetExp());
}

void AMyPlayerController::AddGameScore() const
{
	OWTPlayerState->AddGameScore();
}

void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();

	FInputModeGameOnly InputMode;
	SetInputMode(InputMode);

	HUDWidget = CreateWidget<UHUDWidget>(this, HUDWidgetClass);
	HUDWidget->AddToViewport();

	OWTPlayerState = Cast<AOWTPlayerState>(PlayerState);
	ABCHECK(nullptr != OWTPlayerState);
	HUDWidget->BindPlayerState(OWTPlayerState);
	OWTPlayerState->OnPlayerStateChanged.Broadcast();
}
