// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyFirstProjectile.h"

#include "MyCubeActor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"

AMyFirstProjectile::AMyFirstProjectile()
{
	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	// 只有服务器端绑定委托
	// set up a notification for when this component hits something blocking
	if (HasAuthority())
	{
		CollisionComp->OnComponentHit.AddDynamic(this, &AMyFirstProjectile::OnHit);
	}

	// Players can't walk on it	
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	// Set as root component
	RootComponent = CollisionComp;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;

	// Die after 3 seconds by default
	InitialLifeSpan = 3.0f;

	// Add replication
	bReplicates = true;
}

void AMyFirstProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                               FVector NormalImpulse, const FHitResult& Hit)
{
	/* Only run on server */
	if (!HasAuthority())
		return;
	// Only add impulse and destroy projectile if we hit a physics
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && OtherComp->IsSimulatingPhysics())
	{
		UE_LOG(LogTemp, Log, TEXT("OtherActor Type: %s"), *OtherActor->GetClass()->GetName());
		if (auto Cube = Cast<AMyCubeActor>(OtherActor); Cube != nullptr)
		{
			Cube->OnHit(GetInstigatorController());
		}
		OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());
		Destroy();
	}
}
