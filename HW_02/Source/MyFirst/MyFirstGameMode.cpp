// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyFirstGameMode.h"

#include <unordered_set>

#include "MyCubeActor.h"
#include "MyFirstCharacter.h"
#include "MyFirstPlayerController.h"
#include "MyGameState.h"
#include "BaseGizmos/GizmoElementArrow.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Math/UnitConversion.h"
#include "UObject/ConstructorHelpers.h"

AMyFirstGameMode::AMyFirstGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(
		TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;
	// randomPickNumber
	RandomPickNumber = 1;
}

void AMyFirstGameMode::BeginPlay()
{
	// random pick
	RandomPick();
	//
	InitGameTime();
}

void AMyFirstGameMode::OnTimeUpdated()
{
	auto state = GetGameState<AMyGameState>();
	state->DecreaseTime();
	if (state->GetRemainTime() <= 0)
	{
		// Clear timer
		GetWorldTimerManager().ClearTimer(TimerHandle);
		// End game
		ShutDownGame();
	}
	UE_LOG(LogGameMode, Log, TEXT("TIME PASSED"));
}

/* Finish the game after time consumed */
void AMyFirstGameMode::ShutDownGame()
{
	for (FConstPlayerControllerIterator iter = GetWorld()->GetPlayerControllerIterator(); iter; ++iter)
	{
		if (auto controller = Cast<AMyFirstPlayerController>(*iter))
		{
			controller->ClientGameOver();
		}
	}
}

void AMyFirstGameMode::RandomPick()
{
	TArray<AActor*> Cubes;
	std::unordered_set<int32> IndexSet;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMyCubeActor::StaticClass(), Cubes);
	int32 PickNumber = std::min(RandomPickNumber, Cubes.Num());
	for (int32 i = 0; i < PickNumber; ++i)
	{
		// random pick
		int32 idx = FMath::RandRange(0, Cubes.Num() - 1);
		while (IndexSet.contains(idx))
			idx = FMath::RandRange(0, Cubes.Num() - 1);
		// add to set
		IndexSet.insert(idx);
		// change score and color
		auto cube = Cast<AMyCubeActor>(Cubes[idx]);
		// double score
		cube->Score <<= 1;
		/* set client-side cube to be red */
		cube->bPicked = true;
	}
	
}

void AMyFirstGameMode::InitGameTime()
{
	/* Set Default time to game state */
	GetGameState<AMyGameState>()->SetGameTime(GameDuration);

	GetWorldTimerManager().SetTimer(TimerHandle, this, &AMyFirstGameMode::OnTimeUpdated, 1.0f, true);
}
