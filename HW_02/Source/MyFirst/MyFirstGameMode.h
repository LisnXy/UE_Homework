// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MyFirstGameMode.generated.h"

UCLASS(minimalapi)
class AMyFirstGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	int32 RandomPickNumber;

	/* Total time of the game, default 60s */
	UPROPERTY(EditDefaultsOnly)
	int32 GameDuration = 60;

	FTimerHandle TimerHandle;
	AMyFirstGameMode();
	virtual void BeginPlay() override;

	void OnTimeUpdated();
	void ShutDownGame();

private:
	void RandomPick();
	void InitGameTime();
};
