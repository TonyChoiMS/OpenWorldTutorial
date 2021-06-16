// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePlayWidget.h"
#include "Components/Button.h"
#include "MyPlayerController.h"

void UGamePlayWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ResumeButton = Cast<UButton>(GetWidgetFromName(TEXT("btnResume")));

	if (nullptr != ResumeButton)
	{
		ResumeButton->OnClicked.AddDynamic(this, &UGamePlayWidget::OnClickResume);
	}

	ReturnToTitleButton = Cast<UButton>(GetWidgetFromName(TEXT("btnReturnToTitle")));

	if (nullptr != ReturnToTitleButton)
	{
		ReturnToTitleButton->OnClicked.AddDynamic(this, &UGamePlayWidget::OnClickReturnToTitle);
	}

	RetryGameButton = Cast<UButton>(GetWidgetFromName(TEXT("btnRetryGame")));

	if (nullptr != RetryGameButton)
	{
		RetryGameButton->OnClicked.AddDynamic(this, &UGamePlayWidget::OnClickRetryGame);
	}
}

void UGamePlayWidget::OnClickResume()
{
	auto MyPlayerController = Cast<AMyPlayerController>(GetOwningPlayer());
	ABCHECK(nullptr != MyPlayerController);

	RemoveFromParent();

	MyPlayerController->ChangeInputMode(true);
	MyPlayerController->SetPause(false);
}

void UGamePlayWidget::OnClickReturnToTitle()
{
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("Title"));
}

void UGamePlayWidget::OnClickRetryGame()
{
	auto PlayerController = Cast<AMyPlayerController>(GetOwningPlayer());
	ABCHECK(nullptr != PlayerController);
	PlayerController->RestartLevel();
}

