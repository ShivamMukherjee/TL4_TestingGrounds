// Copyright (c) Shivam Mukherjee 2017

#include "TL4_TestingGrounds.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "Tile.h"


// Sets default values
ATile::ATile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();

	SphereCast(this->GetActorLocation(), 300);
	SphereCast(this->GetActorLocation() + FVector(0, 0, 1000), 300);
}

// Called every frame
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATile::PlaceActors(TSubclassOf<AActor> ToSpawn, int32 MinSpawn, int32 MaxSpawn)
{
	for (size_t i = 0; i < FMath::RandRange(MinSpawn, MaxSpawn); i++)
	{
		FVector SpawnPoint = FMath::RandPointInBox(FBox(FVector(0, -2000, 0), FVector(4000, 2000, 0)));
		AActor* Spawned = GetWorld()->SpawnActor(ToSpawn);
		Spawned->SetActorRelativeLocation(SpawnPoint);
		Spawned->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
	}
}

bool ATile::SphereCast(FVector Location, float Radius)
{
	FHitResult HitResult;
	bool bHasHit = GetWorld()->SweepSingleByChannel(
		HitResult,
		Location,
		Location,
		FQuat::Identity,
		ECollisionChannel::ECC_Camera, /// TODO make custom channel
		FCollisionShape::MakeSphere(Radius)
	);

	FColor DebugColor = bHasHit? FColor::Red : FColor::Green;
	DrawDebugSphere(GetWorld(), Location, Radius, 32, DebugColor, true);
	
	return bHasHit;
}

