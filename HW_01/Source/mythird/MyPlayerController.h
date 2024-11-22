// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

/**
 *
 */
UCLASS()
class MYTHIRD_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()
protected:
	//
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;
private:
	void MoveToMouseCursor();
};
