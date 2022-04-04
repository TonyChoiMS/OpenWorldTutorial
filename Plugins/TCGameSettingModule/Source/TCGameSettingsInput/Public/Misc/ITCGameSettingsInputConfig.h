
#pragma once

#include "TCGameSettingsInputConfigInterface.h"
#include "GameplayTagContainer.h"
#include "Engine/DeveloperSettings.h"
#include "GameFramework/PlayerInput.h"
#include "InputMappingPreset.h"
#include "Engine/Texture.h"
#include "TCGameSettingsInputConfig.generated.h"

USTRUCT()
struct FKeyIconPair
{
	GENERATED_BODY()

	UPROPERTY()
	FKey Key_DEPRECATED;

	UPROPERTY()
	UTexture* Icon_DEPRETACTED = nullptr;
}

