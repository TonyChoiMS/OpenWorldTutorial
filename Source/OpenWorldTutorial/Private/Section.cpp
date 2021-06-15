// Fill out your copyright notice in the Description page of Project Settings.


#include "Section.h"
#include "MyCharacter.h"
#include "ABItemBox.h"
#include "MyPlayerController.h"
#include "OpenWorldGameMode.h"

// Sets default values
ASection::ASection()
{
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));
	RootComponent = Mesh;

	FString AssetPath = TEXT("/Game/Environment/SM_SQUARE.SM_SQUARE");
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_SQUARE(*AssetPath);
	if (SM_SQUARE.Succeeded())
	{
		Mesh->SetStaticMesh(SM_SQUARE.Object);
	}
	else
	{
		ABLOG(Error, TEXT("Failed to load staticmesh asset. : %s"), *AssetPath);
	}

	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TRIGGER"));
	Trigger->SetBoxExtent(FVector(775.0f, 775.0f, 300.0f));
	Trigger->SetRelativeLocation(FVector(0.0f, 0.0f, 250.0f));
	Trigger->SetCollisionProfileName(TEXT("OWTTrigger"));

	Trigger->OnComponentBeginOverlap.AddDynamic(this, &ASection::OnTriggerBeginOverlap);

	FString GateAssetPath = TEXT("/Game/Environment/SM_GATE.SM_GATE");
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_GATE(*GateAssetPath);
	if (!SM_GATE.Succeeded())
	{
		ABLOG(Error, TEXT("Failed to load staticmesh asset. : %s"), *GateAssetPath);
	}
	
	static FName GateSockets[] = { { TEXT("+XGate") }, { TEXT("-XGate") }, { TEXT("+YGate") }, { TEXT("-YGate") } };
	for (FName GateSocket : GateSockets)
	{
		//ABCHECK(Mesh->DoesSocketExist(GateSocket));
		UStaticMeshComponent* NewGate = CreateDefaultSubobject<UStaticMeshComponent>(*GateSocket.ToString());
		NewGate->SetStaticMesh(SM_GATE.Object);
		NewGate->SetupAttachment(RootComponent, GateSocket);
		NewGate->SetRelativeLocation(FVector(0.0f, -80.5f, 0.0f));
		GateMeshes.Add(NewGate);

		UBoxComponent* NewGateTrigger = CreateDefaultSubobject<UBoxComponent>(*GateSocket.ToString().Append(TEXT("Trigger")));
		NewGateTrigger->SetBoxExtent(FVector(100.0f, 100.0f, 300.0f));
		NewGateTrigger->SetupAttachment(RootComponent, GateSocket);
		NewGateTrigger->SetRelativeLocation(FVector(70.0f, 0.0f, 250.0f));
		NewGateTrigger->SetCollisionProfileName(TEXT("OWTTrigger"));
		GateTriggers.Add(NewGateTrigger);

		NewGateTrigger->OnComponentBeginOverlap.AddDynamic(this, &ASection::OnGateTriggerBeginOverlap);
		NewGateTrigger->ComponentTags.Add(GateSocket);
			
	}

	bNoBattle = false;

	EnemySpawnTime = 2.0f;
	ItemBoxSpawnTime = 5.0f;
}

// Called when the game starts or when spawned
void ASection::BeginPlay()
{
	Super::BeginPlay();
	
	SetState(bNoBattle ? ESectionState::COMPLETE : ESectionState::READY);
}

void ASection::SetState(ESectionState NewState)
{
	switch (NewState)
	{
	case ESectionState::READY:
		Trigger->SetCollisionProfileName(TEXT("ABTrigger"));
		for (UBoxComponent* GateTrigger : GateTriggers)
		{
			GateTrigger->SetCollisionProfileName(TEXT("NoCollision"));
		}

		OperateGates(true);
		break;
	case ESectionState::BATTLE:
		Trigger->SetCollisionProfileName(TEXT("NoCollision"));
		for (UBoxComponent* GateTrigger : GateTriggers)
		{
			GateTrigger->SetCollisionProfileName(TEXT("NoCollision"));
		}
		OperateGates(false);

		GetWorld()->GetTimerManager().SetTimer(SpawnNPCTimerHandle,
			FTimerDelegate::CreateUObject(this, &ASection::OnNPCSpawn), EnemySpawnTime, false);

		GetWorld()->GetTimerManager().SetTimer(SpawnItemBoxTimerHandle,
			FTimerDelegate::CreateLambda([this]() -> void 
		{
			FVector2D RandXY = FMath::RandPointInCircle(600.0f);
			GetWorld()->SpawnActor<AABItemBox>(GetActorLocation() + FVector(RandXY, 30.0f), FRotator::ZeroRotator);
		}), ItemBoxSpawnTime, false);

		break;
	case ESectionState::COMPLETE:
		Trigger->SetCollisionProfileName(TEXT("NoCollision"));
		for (UBoxComponent* GateTrigger : GateTriggers)
		{
			GateTrigger->SetCollisionProfileName(TEXT("ABTrigger"));
		}
		OperateGates(true);
		break;
	}

	CurrentState = NewState;
}

void ASection::OperateGates(bool bOpen)
{
	for (UStaticMeshComponent* Gate : GateMeshes)
	{
		Gate->SetRelativeRotation(bOpen ? FRotator(0.0f, -90.0f, 0.0f) : FRotator::ZeroRotator);
	}
}

void ASection::OnTriggerBeginOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (CurrentState == ESectionState::READY)
	{
		SetState(ESectionState::BATTLE);
	}
}

void ASection::OnGateTriggerBeginOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	ABCHECK(OverlappedComponent->ComponentTags.Num() == 1);
	FName ComponentTag = OverlappedComponent->ComponentTags[0];
	FName SocketName = FName(*ComponentTag.ToString().Left(2));
	if (!Mesh->DoesSocketExist(SocketName))
		return;

	FVector NewLocation = Mesh->GetSocketLocation(SocketName);

	TArray<FOverlapResult> OverlapResults;
	FCollisionQueryParams CollisionQueryParam(NAME_None, false, this);
	FCollisionObjectQueryParams ObjectQueryParam(FCollisionObjectQueryParams::InitType::AllObjects);
	bool bResult = GetWorld()->OverlapMultiByObjectType(
		OverlapResults,
		NewLocation,
		FQuat::Identity,
		ObjectQueryParam,
		FCollisionShape::MakeSphere(775.0f),
		CollisionQueryParam
	);

	if (!bResult)
	{
		auto NewSection = GetWorld()->SpawnActor<ASection>(NewLocation, FRotator::ZeroRotator);
	}
	else
	{
		ABLOG(Warning, TEXT("New section Area is not empty"));
	}
}

void ASection::OnNPCSpawn()
{
	GetWorld()->GetTimerManager().ClearTimer(SpawnNPCTimerHandle);
	auto KeyNPC = GetWorld()->SpawnActor<AMyCharacter>(GetActorLocation() + FVector::UpVector * 88.0f, FRotator::ZeroRotator);
	if (nullptr != KeyNPC)
	{
		KeyNPC->OnDestroyed.AddDynamic(this, &ASection::OnKeyNPCDestroyed);
	}
}

void ASection::OnKeyNPCDestroyed(AActor * DestroyedActor)
{
	auto MyCharacter = Cast<AMyCharacter>(DestroyedActor);
	ABCHECK(nullptr != MyCharacter);

	auto MyPlayerController = Cast<AMyPlayerController>(MyCharacter->LastHitBy);
	ABCHECK(nullptr != MyPlayerController);

	auto OpenWorldGameMode = Cast<AOpenWorldGameMode>(GetWorld()->GetAuthGameMode());
	ABCHECK(nullptr != OpenWorldGameMode);
	OpenWorldGameMode->AddScore(MyPlayerController);

	SetState(ESectionState::COMPLETE);
}

void ASection::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	SetState(bNoBattle ? ESectionState::COMPLETE : ESectionState::READY);
}