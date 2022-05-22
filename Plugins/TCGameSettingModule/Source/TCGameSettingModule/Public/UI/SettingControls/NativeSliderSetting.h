#pragma once

#include "SliderSetting.h"
#include "Components/Slider.h"
#include "NativeSliderSetting.generated.h"

/**
 * Setting for a native Unreal Slider
 */
UCLASS(abstract)
class TCGAMESETTINGMODULE_API UNativeSliderSetting : public USliderSetting
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, Category = "Native Slider Setting", meta = (BindWidget))
		USlider* Slider;

	virtual void NativeConstruct() override;

	virtual void UpdateSliderValue_Implementation(float NormalizedValue, float RawValue) override;

	// Only save if handle is released
	virtual bool ShouldSaveCurrentValue_Implementation() const override { return !bMouseCaptureInProgress; }

private:

	UPROPERTY()
	bool bMouseCaptureInProgress;

	UFUNCTION()
	void SliderValueChanged(float NewValue);

	UFUNCTION()
	void SliderMouseCaptureBegin();

	UFUNCTION()
	void SliderMouseCaptureEnd();


};
