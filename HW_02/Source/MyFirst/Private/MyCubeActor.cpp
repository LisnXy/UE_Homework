// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCubeActor.h"
#include "Net/UnrealNetwork.h"
#include "MyPlayerState.h"


// Sets default values
AMyCubeActor::AMyCubeActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	// Init values
	HitCount = 0;
	Score = 0;
	ScaleFactor = 0.5;
	bPicked = false;
	// Setup components
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	// Create the static mesh component
	CubeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CubeMesh"));
	CubeMesh->SetupAttachment(Root); // Attach CubeMesh to the Root component
	CubeMesh->SetRelativeScale3D({1, 1, 1});

	/* Add replication settings */
	bReplicates = true;
	SetReplicateMovement(true);
}

/* Update color when picked. */
void AMyCubeActor::OnPicked()
{
	auto Mater = CubeMesh->GetMaterial(0);
	UMaterialInstanceDynamic* DynamicMaterial = UMaterialInstanceDynamic::Create(Mater, CubeMesh);
	DynamicMaterial->SetVectorParameterValue(FName("Base Color"), FLinearColor::Red);
	CubeMesh->SetMaterial(0, DynamicMaterial);
}

// Called when the game starts or when spawned
void AMyCubeActor::BeginPlay()
{
	Super::BeginPlay();
}

void AMyCubeActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AMyCubeActor, HitCount);
	DOREPLIFETIME(AMyCubeActor, bPicked);
}

void AMyCubeActor::OnHitCountUpdated()
{
	if (!HasAuthority())
	{
		/* Client side */
		if (HitCount == 1)
		{
			/* First hit */
			UE_LOG(LogTemp, Display, TEXT("AMyCubeActor::OnHitCountUpdated"));
			FVector NewScale = CubeMesh->GetComponentScale() * ScaleFactor;
			CubeMesh->SetWorldScale3D(NewScale);
		}
	}
}


// Called every frame
void AMyCubeActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMyCubeActor::OnHit(AController* Player)
{
	/* Only Handle on server */
	if (!HasAuthority())
	{
		return;
	}
	UE_LOG(LogTemp, Log, TEXT("HIT!"));
	++HitCount;
	if (HitCount == 1)
	{
		UE_LOG(LogTemp, Log, TEXT("First HIT"));
		/* first hit, scale to ScaleFactor */
		auto body = CubeMesh->GetBodyInstance();
		FVector NewScale = CubeMesh->GetComponentScale() * ScaleFactor;
		CubeMesh->SetWorldScale3D(NewScale);
	}
	else if (HitCount == 2)
	{
		/* Second hit, destory the actor and add score */
		auto PlayerState = Player->PlayerState;
		auto MyState = Cast<AMyPlayerState>(PlayerState);
		if (MyState)
		{
			MyState->MyScore += Score;
			UE_LOG(LogTemp, Log, TEXT("Score: %d"), MyState->MyScore);
		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT("Score: Controller empty"));
		}
		Destroy();
	}
}
