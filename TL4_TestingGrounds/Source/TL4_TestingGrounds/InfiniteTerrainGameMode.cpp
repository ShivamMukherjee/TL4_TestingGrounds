// Copyright (c) Shivam Mukherjee 2017

#include "TL4_TestingGrounds.h"
#include "InfiniteTerrainGameMode.h"
#include "NavMesh/NavMeshBoundsVolume.h"
#include "EngineUtils.h"
#include "ActorPool.h"


AInfiniteTerrainGameMode::AInfiniteTerrainGameMode()
{
	Score = 0;
	NavMeshBoundsVolumePool = CreateDefaultSubobject<UActorPool>(FName(TEXT("Nav Mesh Bounds Volume Pool")));
}

void AInfiniteTerrainGameMode::PopulateBoundsVolumePool()
{
	for (auto* FoundVolume : TActorRange<ANavMeshBoundsVolume>(GetWorld()))
	{
		AddToPool(FoundVolume);
	}
}

void AInfiniteTerrainGameMode::NewTileConquered()
{
	Score++;
	UE_LOG(LogTestingGrounds, Warning, TEXT("[%s] Score: %i"), *GetName(), Score);
}

void AInfiniteTerrainGameMode::AddToPool(ANavMeshBoundsVolume* VolumeToAdd)
{
	NavMeshBoundsVolumePool->Add(VolumeToAdd);
}