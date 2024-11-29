// Fill out your copyright notice in the Description page of Project Settings.


#include "MyHUD.h"

#include "MyGameState.h"
#include "MyPlayerState.h"


FString UMyHUD::GetEndString()
{
	FString endString = "";
	if (auto state = Cast<AMyGameState>(GetWorld()->GetGameState()))
	{
		TArray<FString> Lines;
		Lines.Reserve(state->PlayerArray.Num());

		for (auto& player : state->PlayerArray)
		{
			auto myPlayer = Cast<AMyPlayerState>(player);
			if (myPlayer)
			{
				Lines.Add(FString::Printf(
					TEXT("Player : %s, Score : %d"),
					*myPlayer->GetPlayerName(),
					myPlayer->MyScore
				));
			}
		}
		endString = FString::Join(Lines, TEXT("\n"));
	}
	return endString;
}
