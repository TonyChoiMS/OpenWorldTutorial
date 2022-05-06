
#pragma once

#include "CoreMinimal.h"

#include "Tickable.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "TCGameSettingsInputSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class TCGAMESETTINGSINPUT_API UTCGameSettingsInputSubsystem : public UGameInstanceSubsystem, public FTickableGameObject
{
	GENERATED_BODY()

protected:
	// FTickableGameObject
	void Tick(float DeltaTime) override;

	// Don't tick CDO
	bool IsTickable() const override { return !this->HasAnyFlags(RF_ClassDefaultObject); }

	TStatId GetStatId() const override { return TStatId(); }
};