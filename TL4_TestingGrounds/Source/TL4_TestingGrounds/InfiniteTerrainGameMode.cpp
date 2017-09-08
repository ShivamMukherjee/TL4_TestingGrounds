// Copyright (c) Shivam Mukherjee 2017

#include "TL4_TestingGrounds.h"
#include "InfiniteTerrainGameMode.h"
#include "AI/Navigation/NavMeshBoundsVolume.h"
#include "EngineUtils.h"


void AInfiniteTerrainGameMode::PopulateBoundsVolumePool()
{
	for (auto* FoundVolume : TActorRange<ANavMeshBoundsVolume>(GetWorld()))
	{
		AddToPool(FoundVolume);
	}
}

void AInfiniteTerrainGameMode::AddToPool(ANavMeshBoundsVolume* VolumeToAdd)
{
	UE_LOG(LogTestingGrounds, Warning, TEXT("Found Actor: %s"), *VolumeToAdd->GetName())
}