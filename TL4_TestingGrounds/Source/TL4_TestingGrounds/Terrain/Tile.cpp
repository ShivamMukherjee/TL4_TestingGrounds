// Copyright (c) Shivam Mukherjee 2017

#include "TL4_TestingGrounds.h"
#include "Engine/World.h"
#include "NavigationSystem.h"

#include "InfiniteTerrainGameMode.h"
#include "ActorPool.h"
#include "Tile.h"


// Sets default values
ATile::ATile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	NavigationBoundsOffset = FVector(2000, 0, 0);

	MinExtent = FVector(0, -2000, 0);
	MaxExtent = FVector(4000, 2000, 0);
}

// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();
	
}


void ATile::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (Pool && NavMeshBoundsVolume)
	{
		Pool->Return(NavMeshBoundsVolume);
	}
}

void ATile::UpdateTileConquered()
{
	auto* AuthGameMode = Cast<AInfiniteTerrainGameMode>(GetWorld()->GetAuthGameMode());
	if (AuthGameMode != nullptr && !bIsTileConquered)
	{
		AuthGameMode->NewTileConquered();
		bIsTileConquered = true;
	}
}

// Called every frame
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


template<class A>
void ATile::RandomlyPlaceActors(const TSubclassOf<A>& ToSpawn, int32 MinSpawn, int32 MaxSpawn, float Radius, float MinScale, float MaxScale)
{
	int SpawnCount = FMath::RandRange(MinSpawn, MaxSpawn);
	for (int32 i = 0; i < SpawnCount; i++)
	{
		FSpawnPosition SpawnPosition;
		SpawnPosition.UniformScale = FMath::RandRange(MinScale, MaxScale);
		if (FoundEmptyLocation(SpawnPosition.Location, Radius * SpawnPosition.UniformScale))
		{
			SpawnPosition.YawRotation = FMath::RandRange(-180.f, +180.f);
			PlaceActor(ToSpawn, SpawnPosition);
		}
	}
}


void ATile::PlaceActors(TSubclassOf<AActor> ToSpawn, int32 MinSpawnCount, int32 MaxSpawnCount, float ClearanceRadius, float MinScale, float MaxScale)
{
	RandomlyPlaceActors(ToSpawn, MinSpawnCount, MaxSpawnCount, ClearanceRadius, MinScale, MaxScale);
}


void ATile::PlaceAIPawns(TSubclassOf<APawn> ToSpawn, int32 MinSpawnCount, int32 MaxSpawnCount, float ClearanceRadius)
{
	RandomlyPlaceActors(ToSpawn, MinSpawnCount, MaxSpawnCount, ClearanceRadius, 1, 1);
}


void ATile::SetActorPool(UActorPool* InPool)
{
	Pool = InPool;
	PositionNavMeshBoundsVolume();
}


bool ATile::FoundEmptyLocation(FVector& OutLocation, float Radius)
{
	FBox Bounds(MinExtent, MaxExtent);

	const int32 MAX_ATTEMPTS = 100;

	for (int32 i = 0; i < MAX_ATTEMPTS; i++)
	{
		FVector CandidatePoint = FMath::RandPointInBox(Bounds);

		if (CanSpawnAtLocation(CandidatePoint, Radius))
		{
			OutLocation = CandidatePoint;
			return true;
		}
	}

	return false;
}


void ATile::PlaceActor(const TSubclassOf<AActor>& ToSpawn, const FSpawnPosition& SpawnPosition)
{
	AActor* Spawned = GetWorld()->SpawnActor<AActor>(
		ToSpawn,
		SpawnPosition.Location,
		FRotator(0, SpawnPosition.YawRotation, 0)
		);
	if (Spawned != nullptr)
	{
		Spawned->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
		Spawned->SetActorScale3D(FVector(SpawnPosition.UniformScale));
	}
}


void ATile::PlaceActor(const TSubclassOf<APawn>& ToSpawn, const FSpawnPosition& SpawnPosition)
{
	APawn* Spawned = GetWorld()->SpawnActor<APawn>(
		ToSpawn,
		SpawnPosition.Location,
		FRotator(0, SpawnPosition.YawRotation, 0)
		);
	if (Spawned != nullptr)
	{
		Spawned->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
		Spawned->SpawnDefaultController();
		Spawned->Tags.Add(FName(TEXT("PatrolGuard")));
	}
}


bool ATile::CanSpawnAtLocation(FVector Location, float ClearanceRadius)
{
	FHitResult HitResult;
	FVector GlobalLocation = ActorToWorld().TransformPosition(Location);
	return !GetWorld()->SweepSingleByChannel(
		HitResult,
		GlobalLocation,
		GlobalLocation,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(ClearanceRadius)
	);
}


void ATile::PositionNavMeshBoundsVolume()
{
	NavMeshBoundsVolume = Pool->Checkout();
	
	if (NavMeshBoundsVolume == nullptr)
	{
		UE_LOG(LogTestingGrounds, Error, TEXT("[%s] Not enough actors in pool."), *GetName());
	}
	else
	{
		UE_LOG(LogTestingGrounds, Warning, TEXT("[%s] Checked out: {%s}"), *GetName(), *NavMeshBoundsVolume->GetName());
		NavMeshBoundsVolume->SetActorLocation(GetActorLocation() + NavigationBoundsOffset);
		FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld())->Build();
	}
}