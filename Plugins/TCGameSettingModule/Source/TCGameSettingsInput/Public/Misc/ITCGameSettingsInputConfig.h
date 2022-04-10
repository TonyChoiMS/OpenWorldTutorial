
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
};

// Set of key icons
USTRUCT()
struct FKeyIconSet
{
	GENERATED_BODY()

	// Tags to identify this icon set
	// May include platform such as "XBox" or "PlayStation" and/or variations such as "Small" or "Large"
	UPROPERTY(config, EditAnywhere, Category = "Key Icon Set")
	FGameplayTagContainer Tags;

	// Icons defined for different keys
	UPROPERTY(config, EditAnywhere, Category = "Key Icon Set")
	TMap<FKey, TSoftObjectPtr<UTexture>> IconMap;

	UPROPERTY()
	TArray<FKeyIconPair> Icons_DEPRECATED;

	// Return the icon texture for the given key
	UTexture* GetIcon(FKey Key) const;
};

// Defines a group of keys which should be separated from other keys
USTRUCT()
struct FKeyGroup
{
	GENERATED_BODY()

	// Tag to identify this key group
	UPROPERTY(config, EditAnywhere, Category = "Key Group")
	FGameplayTag KeyGroupTag;

	// If true, will include all gamepad keys in this key group
	UPROPERTY(config, EditAnywhere, Category = "Key Group")
	bool bUseGamepadKeys;

	// If true, will include all keys that are not gamepad keys in this key group
	UPROPERTY(config, EditAnywhere, Category = "Key Group")
	bool bUseNonGamepadKeys;

	// Keys to include in this key group
	UPROPERTY(config, EditAnywhere, Category =" Key Group", meta = (TitleProperty = "KeyName"))
	TArray<FKey> Keys;

	bool Contains(FKey Key) const
	{
		const bool bIsGamepad = Key.IsGamepadKey();
		if (bIsGamepad && bUseGamepadKeys)
			return true;
		if (!bIsGamepad && bUseNonGamepadKeys)
			return true;
		return Keys.Contains(Key);
	}
};

// Represents pairing of a button key and a scale, use to associate buttons with an axis
USTRUCT()
struct FKeyScale
{
	GENERATED_BODY()

	// Button Key
	UPROPERTY(config, EditAnywhere, Category = "Key Scale")
	FKey Key;

	// Scale of the axis that the button key should be associated with
	UPROPERTY(config, EditAnywhere, Category = "Key Scale")
	float Scale;

	FKeyScale() : Scale(1.f) {}

	FKeyScale(FKey InKey) : Key(InKey), Scale (1.f) {}

	FKeyScale (FKey InKey, float InScale) : Key(InKey), Scale(InScale) {}
};