#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "TCGameSettingsInputConfigInterface.generated.h"

struct FKey;
struct FInputMappingPreset;
struct FKeyGroup;
struct FGameplayTag;

UINTERFACE()
class UTCGameSettingsInputConfigInterface : public UInterface
{
	GENERATED_BODY()
};

// Interface to access input config
class TCGAMESETTINGSINPUT_API ITCGameSettingsInputConfigInterface
{
	GENERATED_BODY()

public:
	virtual bool ShouldAllowMultipleBindingsPerKey() const = 0;

	virtual bool ShouldBindingsBeUniqueBetweenMappingGroups(int32 MappingGroupA, int32 MappingGroupB) const = 0;

	virtual FInputMappingPreset GetInputPresetByTag(FGameplayTag PresetTag) const = 0;
	virtual TArray<FName> GetPreservedActions() const = 0;
	virtual TArray<FName> GetPreservedAxes() const = 0;
	virtual const TArray<FKeyGroup>& GetKeyGroups() const = 0;
	virtual FGameplayTag GetKeyGroupOfKey(FKey Key) const = 0;

	// 이미 키가 Defined되있을 경우 True 반환
	virtual bool IsKeyGroupDefined(FGameplayTag KeyGroupTag) const = 0;

	// Axis 키인경우 True 반환
	virtual bool IsAxisKEy(FKey Key) const = 0;
};

