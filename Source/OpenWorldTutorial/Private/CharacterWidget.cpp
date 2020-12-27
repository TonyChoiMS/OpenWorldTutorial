// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterWidget.h"
#include "CharacterStatComponent.h"
#include "Components/ProgressBar.h"

void UCharacterWidget::BindCharacterStat(UCharacterStatComponent* NewCharacterStat)
{
	ABCHECK(nullptr != NewCharacterStat);

	CurrentCharacterStat = NewCharacterStat;
	NewCharacterStat->OnHPChanged.AddUObject(this, &UCharacterWidget::UpdateHPWidget);
}

void UCharacterWidget::NativeConstruct()
{
	Super::NativeConstruct();
	HPPProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("PB_HPBar")));
	ABCHECK(nullptr != HPPProgressBar);
	UpdateHPWidget();
}

void UCharacterWidget::UpdateHPWidget()
{
	if (nullptr != HPPProgressBar)
	{
		HPPProgressBar->SetPercent(CurrentCharacterStat->GetHPRatio());
	}
}
