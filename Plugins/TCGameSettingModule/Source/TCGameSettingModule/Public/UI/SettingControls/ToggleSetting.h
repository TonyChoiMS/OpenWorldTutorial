#pragma once

#include "UI/TCGameSettingWidget.h"
#include "ToggleSetting.generated.h"

/**
 * Base Setting with generic toggle functionality (Such as a checkbox or switch)
 */
UCLASS(abstract)
class TCGAMESETTINGMODULE_API UToggleSetting : public UTCGameSettingWidget
{
	GENERATED_BODY()

protected:
	virtual void UpdateSelection_Implementation(const FString& Value) override;

	// Called to update the widget with a new state
	UFUNCTION(BlueprintNativeEvent, Category = "Toggle Setting")
	void UpdateToggleState(bool State);

	// Takes a boolean state and applies the setting
	UFUNCTION(BlueprintCallable, Category = "Toogle Setting")
	void ToggleStateUpdated(bool State);
};