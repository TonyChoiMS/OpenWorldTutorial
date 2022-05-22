#include "UI/BindCaptureButton.h"
#include "TCGameSettingsError.h"

UBindCaptureButton::UBindCaptureButton(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, CapturePromptZOrder(1)
{
}

UBindCapturePrompt* UBindCaptureButton::StartCapture()
{
	if (!ensure(BindCapturePromptClass))
	{
		FTCGameSettingsError::LogInvalidClass(GetClass(), "BindCapturePromptClass");
		return nullptr;
	}

	Prompt = CreateWidget<UBindCapturePrompt>(GetOwningPlayer(), BindCapturePromptClass);

	if (!ensure(Prompt))
	{
		FTCGameSettingsError::LogWIdgetCreationFailed(GetClass(), "BindCapturePrompt");
		return nullptr;
	}

	Prompt->OnChordCaptured.AddDynamic(this, &UBindCaptureButton::ChordCaptured);
	Prompt->KeyGroup = KeyGroup;
	InitializePrompt(Prompt);
	return Prompt;
}

void UBindCaptureButton::InitializePrompt_Implementation(UBindCapturePrompt* PromptWidget)
{
	// Add the prompt straight to the viewport
	PromptWidget->AddToViewport(CapturePromptZOrder);
}

void UBindCaptureButton::ChordCaptured(FCapturedInput CapturedInput)
{
	OnChordCaptured.Broadcast(CapturedInput);
}