#include "UI/ActionLabel.h"
#include "Misc/ITCGameSettingsInputConfig.h"
#include "InputMappingManager.h"
#include "Blueprint/WidgetTree.h"
#include "TCGameSettingsError.h"

void UActionLabel::InitializeLabel()
{
	UpdateLabel();
}

void UActionLabel::UpdateLabel_Implementation()
{
	const FInputActionKeyMapping Mapping = UInputMappingManager::Get()->GetPlayerActionMapping(GetOwningPlayer(), ActionName, MappingGroup, KeyGroup, bUsePlayerKeyGroup);

	UpdateKeyLabels(Mapping);
}

UKeyLabel* UActionLabel::CreateLabel()
{
	if (!ensure(KeyLabelWidgetClass))
	{
		return nullptr;
	}

	UKeyLabel* NewKeyLabel = nullptr;

	if (APlayerController* OwningPlayer = GetOwningPlayer())
	{
		NewKeyLabel = CreateWidget<UKeyLabel>(OwningPlayer, KeyLabelWidgetClass);
	}
	else if (UWorld* World = GetWorld())
	{
		NewKeyLabel = CreateWidget<UKeyLabel>(World, KeyLabelWidgetClass);
	}

	if (!ensure(NewKeyLabel))
	{
		FTCGameSettingsError::LogWIdgetCreationFailed(GetClass(), "KeyLabel");
		return nullptr;
	}

	return NewKeyLabel;
}

UKeyLabel* UActionLabel::CreateLabel(const FText& LabelOverride)
{
	if (UKeyLabel* Label = CreateLabel())
	{
		Label->LabelOverride = LabelOverride;
		return Label;
	}

	return nullptr;
}

void UActionLabel::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (GetKeyContainer())
	{
		GetKeyContainer()->ClearChildren();

		if (!ensure(KeyLabelWidgetClass))
		{
			FTCGameSettingsError::LogInvalidClass(GetClass(), "KeyLabelWidgetClass");
		}
		else
		{
			// Construct labels for each key and separators
			PrimaryKeyLabel = CreateLabel();
			ShiftLabel = CreateLabel(UInputMappingManager::GetInputConfigStatic()->ShiftModifierOverrideText);
			CtrlLabel = CreateLabel(UInputMappingManager::GetInputConfigStatic()->CtrlModifierOverrideText);
			AltLabel = CreateLabel(UInputMappingManager::GetInputConfigStatic()->AltModifierOverrideText);
			CmdLabel = CreateLabel(UInputMappingManager::GetInputConfigStatic()->CmdModifierOverrideText);

			GetKeyContainer()->AddChild(ShiftLabel);
			ShiftSeparator = AddSeparatorIfValid();

			GetKeyContainer()->AddChild(CtrlLabel);
			CtrlSeparator = AddSeparatorIfValid();

			GetKeyContainer()->AddChild(AltLabel);
			AltSeparator = AddSeparatorIfValid();

			GetKeyContainer()->AddChild(CmdLabel);
			CmdSeparator = AddSeparatorIfValid();

			GetKeyContainer()->AddChild(PrimaryKeyLabel);

			UpdateLabel();
		}
	}
}

void UActionLabel::UpdateKeyLabels(FInputActionKeyMapping Mapping)
{
	if (PrimaryKeyLabel)
	{
		PrimaryKeyLabel->Key = Mapping.Key;
		PrimaryKeyLabel->IconTags = IconTags;
		PrimaryKeyLabel->UpdateKeyLabel();
	}

	if (ShiftLabel)
	{
		ShiftLabel->Key = EKeys::LeftShift;
		ShiftLabel->IconTags = IconTags;
		ShiftLabel->UpdateKeyLabel();
	}

	if (CtrlLabel)
	{
		CtrlLabel->Key = EKeys::LeftControl;
		CtrlLabel->IconTags = IconTags;
		CtrlLabel->UpdateKeyLabel();
	}

	if (AltLabel)
	{
		AltLabel->Key = EKeys::LeftAlt;
		AltLabel->IconTags = IconTags;
		AltLabel->UpdateKeyLabel();
	}

	if (CmdLabel)
	{
		CmdLabel->Key = EKeys::LeftCommand;
		CmdLabel->IconTags = IconTags;
		CmdLabel->UpdateKeyLabel();
	}

	SetModifierKeyLabelVisibility(ShiftLabel, ShiftSeparator, Mapping.bShift);
	SetModifierKeyLabelVisibility(CtrlLabel, CtrlSeparator, Mapping.bCtrl);
	SetModifierKeyLabelVisibility(AltLabel, AltSeparator, Mapping.bAlt);
	SetModifierKeyLabelVisibility(CmdLabel, CmdSeparator, Mapping.bCmd);
}

void UActionLabel::SetModifierKeyLabelVisibility(UKeyLabel* KeyLabel, UWidget* KeySeparator, bool bVisibility)
{
	if (KeyLabel)
		KeyLabel->SetVisibility(bVisibility ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);

	if (KeySeparator)
		KeySeparator->SetVisibility(bVisibility ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
}

UWidget* UActionLabel::AddSeparatorIfValid()
{
	if (!ensure(KeySeparatorWidgetClass))
	{
		FTCGameSettingsError::LogError(FString::Printf(TEXT("%s: KeySeparatorWidgetClass is not valid"), *GetName()));
		return nullptr;
	}

	UWidget* Separator = WidgetTree->ConstructWidget<UWidget>(KeySeparatorWidgetClass);
	GetKeyContainer()->AddChild(Separator);
	return Separator;
}
