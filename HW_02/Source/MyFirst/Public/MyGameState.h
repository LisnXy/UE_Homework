// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "MyGameState.generated.h"

/**
 * 
 */
UCLASS()
class MYFIRST_API AMyGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	UFUNCTION()
	FORCEINLINE void SetGameTime(int32 NewTime)
	{
		RemainTime = NewTime;
	};

	UFUNCTION()
	FORCEINLINE void DecreaseTime()
	{
		--RemainTime;
	}

	UFUNCTION(BlueprintCallable)
	int32 GetRemainTime() const
	{
		return RemainTime;
	}

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly)
	int32 RemainTime{};
};
