#include "InputMappingPreset.h"

FInputMappingPreset::FInputMappingPreset(FGameplayTag InTag, TArray<FInputActionKeyMapping> ActionMappings, TArray<FInputAxisKeyMapping> AxisMappings)
{
	PresetTag = InTag;

	InputLayout.SetMappings(ActionMappings, AxisMappings);
}

void FInputMappingPreset::SetConfig(TWeakInterfacePtr<const ITCGameSettingsInputConfigInterface> InConfig)
{
	InputLayout.SetConfig(InConfig);
}
