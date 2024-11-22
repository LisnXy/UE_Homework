// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPlayerController.h"

void AMyPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	MoveToMouseCursor();
}

void AMyPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
}

void AMyPlayerController::MoveToMouseCursor()
{
	APawn* ControlledPawn = GetPawn();
	if (ControlledPawn)
	{
		FHitResult HitResult;
		if (GetHitResultUnderCursor(ECC_Visibility, true, HitResult))
		{
			FVector TargetLocation = HitResult.Location;
			FVector PawnLocation = ControlledPawn->GetActorLocation();
			FVector Direction = (TargetLocation - PawnLocation).GetSafeNormal();
			if (!Direction.IsZero())
			{
				ControlledPawn->AddMovementInput(Direction);
				Direction.Z = 0;
				FRotator NewRotation = Direction.Rotation();
				ControlledPawn->SetActorRotation(NewRotation);
			}
		}
	}
}