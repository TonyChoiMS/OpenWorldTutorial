// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"
#include "HUDWidget.h"
#include "OWTPlayerState.h"
#include "MyCharacter.h"
#include "GamePlayWidget.h"
#include "GamePlayResultWidget.h"
#include "OWTGameStateBase.h"


AMyPlayerController::AMyPlayerController()
{
	static ConstructorHelpers::FClassFinder<UHUDWidget> UI_HUD_C(TEXT("/Game/UI/UI_HUD.UI_HUD_C"));

	if (UI_HUD_C.Succeeded())
	{
		HUDWidgetClass = UI_HUD_C.Class;
	}

	static ConstructorHelpers::FClassFinder<UGamePlayWidget> UI_MENU_C(TEXT("/Game/UI/UI_Menu.UI_Menu_C"));
	if (UI_MENU_C.Succeeded())
	{
		MenuWidgetClass = UI_MENU_C.Class;
	}

	static ConstructorHelpers::FClassFinder<UGamePlayWidget> UI_RESULT_C(TEXT("/Game/UI/UI_Result.UI_Result_C"));
	if (UI_RESULT_C.Succeeded())
	{
		ResultWidgetClass = UI_RESULT_C.Class;
	}
}

void AMyPlayerController::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	ABLOG_S(Warning);
}

void AMyPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAction(TEXT("GamePause"), EInputEvent::IE_Pressed, this, &AMyPlayerController::OnGamePause);
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

void AMyPlayerController::ChangeInputMode(bool bGameMode)
{
	if (bGameMode)
	{
		SetInputMode(GameInputMode);
		bShowMouseCursor = false;
	}
	else
	{
		SetInputMode(UIInputMode);
		bShowMouseCursor = true;
	}
}

void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();

	ChangeInputMode(true);

	HUDWidget = CreateWidget<UHUDWidget>(this, HUDWidgetClass);
	ABCHECK(nullptr != HUDWidget);
	HUDWidget->AddToViewport(1);

	ResultWidget = CreateWidget<UGamePlayResultWidget>(this, ResultWidgetClass);
	ABCHECK(nullptr != ResultWidget);
	
	OWTPlayerState = Cast<AOWTPlayerState>(PlayerState);
	ABCHECK(nullptr != OWTPlayerState);
	HUDWidget->BindPlayerState(OWTPlayerState);
	OWTPlayerState->OnPlayerStateChanged.Broadcast();
}

void AMyPlayerController::OnGamePause()
{
	MenuWidget = CreateWidget<UGamePlayWidget>(this, MenuWidgetClass);
	ABCHECK(nullptr != MenuWidget);
	// AddToViewport에 int값을 넘길 경우 해당 값이 UI의 ZOrder로 사용됨.
	// 값이 클수록 더 위에 그려짐.
	MenuWidget->AddToViewport(3);

	SetPause(true);
	ChangeInputMode(false);
}

void AMyPlayerController::ShowResultUI()
{
	auto GameState = Cast<AOWTGameStateBase>(UGameplayStatics::GetGameState(this));
	ABCHECK(nullptr != GameState);
	ResultWidget->BindGameState(GameState);

	ResultWidget->AddToViewport();
	ChangeInputMode(false);
}
