// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyCubeActor.generated.h"

UCLASS()
class MYFIRST_API AMyCubeActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMyCubeActor();
	// Score, added to player when destroyed
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	int32 Score;

	UPROPERTY(ReplicatedUsing=OnPicked, VisibleAnywhere, BlueprintReadOnly, Category = "GamePlay")
	bool bPicked;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	float ScaleFactor;

	// Root component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USceneComponent* Root;

	// Static Mesh component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* CubeMesh;

	UFUNCTION()
	void OnPicked();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// hit count, increased each time get hit
	UPROPERTY(ReplicatedUsing=OnHitCountUpdated, BlueprintReadOnly, Category = "Gameplay")
	int32 HitCount;
	

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION()
	void OnHitCountUpdated();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void OnHit(AController* Player);
	
};
