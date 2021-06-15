// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterSelectWidget.h"
#include "ABCharacterSetting.h"
#include "OpenWorldGameInstance.h"
#include "EngineUtils.h"
#include "Animation/SkeletalMeshActor.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "OWTSaveGame.h"
#include "OWTPlayerState.h"

void UCharacterSelectWidget::NextCharacter(bool bForward)
{
	bForward ? CurrentIndex++ : CurrentIndex--;

	if (CurrentIndex == -1)
	{
		CurrentIndex = MaxIndex - 1;
	}

	if (CurrentIndex == MaxIndex)
	{
		CurrentIndex = 0;
	}

	auto CharacterSetting = GetDefault <UABCharacterSetting>();
	auto AssetRef = CharacterSetting->CharacterAssets[CurrentIndex];

	auto OWTGameInstance = GetWorld()->GetGameInstance<UOpenWorldGameInstance>();
	ABCHECK(nullptr != OWTGameInstance);
	ABCHECK(TargetComponent->IsValidLowLevel());

	USkeletalMesh* Asset = OWTGameInstance->StreamableManager.LoadSynchronous<USkeletalMesh>(AssetRef);
	if (nullptr != Asset)
	{
		TargetComponent->SetSkeletalMesh(Asset);
	}
}

void UCharacterSelectWidget::NativeConstruct()
{
	Super::NativeConstruct();

	CurrentIndex = 0;
	auto CharacterSetting = GetDefault<UABCharacterSetting>();
	MaxIndex = CharacterSetting->CharacterAssets.Num();

	for (TActorIterator<ASkeletalMeshActor> It(GetWorld()); It; ++It)
	{
		TargetComponent = It->GetSkeletalMeshComponent();
		break;
	}

	PrevButton = Cast<UButton>(GetWidgetFromName(TEXT("btnPrev")));
	ABCHECK(nullptr != PrevButton);
	PrevButton->OnClicked.AddDynamic(this, &UCharacterSelectWidget::OnClickPrev);

	NextButton = Cast<UButton>(GetWidgetFromName(TEXT("btnNext")));
	ABCHECK(nullptr != NextButton);
	NextButton->OnClicked.AddDynamic(this, &UCharacterSelectWidget::OnClickNext);

	TextBox = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("edtPlayerName")));

	ConfirmButton = Cast<UButton>(GetWidgetFromName(TEXT("btnConfirm")));
	ABCHECK(nullptr != ConfirmButton);
	ConfirmButton->OnClicked.AddDynamic(this, &UCharacterSelectWidget::OnClickConfirm);
}

void UCharacterSelectWidget::OnClickPrev()
{
	NextCharacter(false);
}

void UCharacterSelectWidget::OnClickNext()
{
	NextCharacter(true);
}

void UCharacterSelectWidget::OnClickConfirm()
{
	FString CharacterName = TextBox->GetText().ToString();
	if (CharacterName.Len() <= 0 || CharacterName.Len() > 10)
		return;

	UOWTSaveGame* NewPlayerData = NewObject<UOWTSaveGame>();
	NewPlayerData->PlayerName = CharacterName;
	NewPlayerData->Level = 1;
	NewPlayerData->Exp = 0;
	NewPlayerData->HighScore = 0;
	NewPlayerData->CharacterIndex = CurrentIndex;

	auto OWTPlayerState = GetDefault<AOWTPlayerState>();
	if (UGameplayStatics::SaveGameToSlot(NewPlayerData, OWTPlayerState->SaveSlotName, 0))
	{
		UGameplayStatics::OpenLevel(GetWorld(), TEXT("Gameplay"));
	}
	else
	{
		ABLOG(Error, TEXT("SaveGame Error"));
	}
}