// Copyright Epic Games, Inc. All Rights Reserved.


#include "MyFirstPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "MyGameState.h"
#include "MyPlayerState.h"
#include "Blueprint/UserWidget.h"
#include "Engine/LocalPlayer.h"
#include "GameFramework/Character.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Kismet/GameplayStatics.h"

void AMyFirstPlayerController::ClientGameOver_Implementation()
{
	// TODO 显示结束界面 & 冻结输入
	DisableInput(this);
	bBlockInput = true;
	SetIgnoreLookInput(true);
	SetIgnoreMoveInput(true);
	if (InputComponent)
	{
		InputComponent->Deactivate();
	}
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(
		GetLocalPlayer());
	if (Subsystem)
	{
		// 移除所有输入映射上下文
		Subsystem->ClearAllMappings();
	}

	auto widget = CreateWidget<UUserWidget>(this, EndGameHUDClass);
	if (widget)
	{	
		widget->AddToViewport();
	}
	/*auto state = Cast<AMyGameState>(GetWorld()->GetGameState());
	if (state)
	{
		 for (auto &player : state->PlayerArray)
		 {
			 if (auto myPlayer = Cast<AMyPlayerState>(player))
			 {
				 UE_LOG(LogTemp, Display, TEXT("Player %s: %d"), *myPlayer->GetPlayerName(), myPlayer->MyScore);
			 }
		 }
	}*/
}

void AMyFirstPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// get the enhanced input subsystem
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(
		GetLocalPlayer()))
	{
		// add the mapping context so we get controls
		Subsystem->AddMappingContext(InputMappingContext, 0);
	}
}
