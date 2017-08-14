// Copyright (c) Shivam Mukherjee 2017

#include "TL4_TestingGrounds.h"
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
	
}

// Called every frame
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATile::PlaceActors(const TSubclassOf<AActor>& ToSpawn, int32 MinSpawn, int32 MaxSpawn)
{
	for (size_t i = 0; i < FMath::RandRange(MinSpawn, MaxSpawn); i++)
	{
		FVector SpawnPoint = FMath::RandPointInBox(FBox(FVector(0, -2000, 0), FVector(4000, 2000, 0)));
		AActor* Spawned = GetWorld()->SpawnActor(ToSpawn);
	}
}

