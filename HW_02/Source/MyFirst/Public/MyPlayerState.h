// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "MyPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class MYFIRST_API AMyPlayerState : public APlayerState
{
	GENERATED_BODY()
public:
	AMyPlayerState();
	UPROPERTY(Replicated, Category = Gameplay, BlueprintGetter=GetMyScore)
	int32 MyScore;
	UFUNCTION(BlueprintGetter)
	int32 GetMyScore() const
	{
		return MyScore;
	};
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
