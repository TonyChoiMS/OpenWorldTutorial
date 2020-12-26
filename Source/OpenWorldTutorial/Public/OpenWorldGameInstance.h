// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "OpenWorldTutorial.h"
#include "Engine/DataTable.h"
#include "Engine/GameInstance.h"
#include "OpenWorldGameInstance.generated.h"

// 언리얼에서 구조체를 생성할 때, 언리얼이 지정한 규칙에 따라줘야 에디터 인터페이스에서 연동해서 사용할 수 있다.
USTRUCT(BlueprintType)
struct FABCharacterData : public FTableRowBase
{
	GENERATED_BODY()
	
public:
	FABCharacterData() : Level(1), MaxHP(100.0f), Attack(10.0f), DropExp(10), NextExp(30) {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	int32 Level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	float MaxHP;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	float Attack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	int32 DropExp;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	int32 NextExp;
};

/**
 * 
 */
UCLASS()
class OPENWORLDTUTORIAL_API UOpenWorldGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public: 
	UOpenWorldGameInstance();

	virtual void Init() override;
	FABCharacterData* GetABCharacterData(int32 Level);

private:
	UPROPERTY()
	class UDataTable* ABCharacterTable;
};
