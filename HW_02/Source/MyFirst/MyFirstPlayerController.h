// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Blueprint/UserWidget.h"
#include "MyFirstPlayerController.generated.h"


class UInputMappingContext;

/**
 *
 */
UCLASS()
class MYFIRST_API AMyFirstPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	UFUNCTION(Client, Reliable)
	void ClientGameOver();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HUD)
	TSubclassOf<class UUserWidget> EndGameHUDClass;
protected:
	/** Input Mapping Context to be used for player input */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputMappingContext* InputMappingContext;


	// Begin Actor interface
protected:
	virtual void BeginPlay() override;

	
	// End Actor interface
};
