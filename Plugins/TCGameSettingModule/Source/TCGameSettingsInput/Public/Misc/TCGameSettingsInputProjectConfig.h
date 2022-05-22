#pragma once

#include "CoreMinimal.h"
#include "ITCGameSettingsInputConfig.h"
#include "TCGameSettingsInputProjectConfig.generated.h"

/**
 * Config Subclass used for the page in project settings
 * This is separate to the base class, so that project settings do not affect the default values of the base class objects (which makes them easier to test)
 */
UCLASS()
class TCGAMESETTINGSINPUT_API UTCGameSettingsInputProjectConfig : public UTCGameSettingsInputConfig
{
	GENERATED_BODY()

public:
	
	UTCGameSettingsInputProjectConfig();

	// Returns the key group that contains the given key
	UFUNCTION(BlueprintPure, Category = "TC Game Settings Config", DisplayName = "Get Key Friendly Name")
	static FText GetKeyFriendlyNameStatic(FKey Key);

	// Returns the key group that contains the given key
	UFUNCTION(BlueprintPure, Category = "TC Game Settings Config", DisplayName = "Get Key Group")
	static FGameplayTag GetKeyGroupStatic(FKey Key);

	/**
	 * Synchronously load all key icon textures in any KeyIconSet(s) with all of the given tags
	 * Returns all textures that were loaded, which should be stored as a variable for as long as the textures need to remain loaded
	 */
	UFUNCTION(BlueprintCallable, Category = "TC Game Settings Config")
	static TArray<UTexture*> LoadKeyIcons(FGameplayTagContainer KeyIconTags);

#if WITH_EDITOR
	virtual bool SupportsAutoRegistration() const override { return true; }
	virtual FText GetSectionText() const override;
	virtual FText GetSectionDescription() const override;
#endif

	virtual void PostInitProperties() override;
};

