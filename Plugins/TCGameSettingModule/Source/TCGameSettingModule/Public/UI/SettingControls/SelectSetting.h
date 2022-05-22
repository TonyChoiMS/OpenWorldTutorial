#pragma once

#include "UI/TCGameSettingWidget.h"
#include "Misc/SettingOptionFactory.h"
#include "SelectSetting.generated.h"

/**
 * Base class for any Setting containing multiple pre-defined options
 */
UCLASS(abstract)
class TCGAMESETTINGMODULE_API USelectSetting : public UTCGameSettingWidget
{
	GENERATED_BODY()

public:
	// predfined options
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Select Setting")
	TArray<FSettingOption> Options;

	// Factory to use to dynamically create options
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Select Setting")
	TSubclassOf<USettingOptionFactory> OptionFactory;

	/**
	 * Call to trigger re-evaluation of Option Factory and reconstruction of available options
	 * Does not modify the selection even if the selected option is removed
	 */
	 UFUNCTION(BlueprintCallable, Category = "Select Setting")
	 void RegeneratedOptions();

protected:
	virtual void NativePreConstruct() override;

	UFUNCTION(BlueprintNativeEvent, Category = "Select Setting")
	void UpdateOptions(const TArray<FSettingOption>& InOptions);

	bool HasOptionWithValue(FString Value) const;

	bool HasOptionWithLabel(FText Label) const;

	FSettingOption GetOptionByValue(FString Value) const;

	FSettingOption GetOptionByLabel(FText Label) const;

	bool IsUpdatingSettingOptions() const { return bUpdatingSettingOptions; }

private:
	UPROPERTY()
	bool bUpdatingSettingOptions;

	TArray<FSettingOption> GetCombinedOptions() const;

	void DispatchUpdateOptions(const TArray<FSettingOption>& InOptions);
};