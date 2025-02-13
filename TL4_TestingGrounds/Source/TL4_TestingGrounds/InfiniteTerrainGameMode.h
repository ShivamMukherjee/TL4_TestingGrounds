// Copyright (c) Shivam Mukherjee 2017

#pragma once

#include "CoreMinimal.h"
#include "TL4_TestingGroundsGameMode.h"
#include "InfiniteTerrainGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TL4_TESTINGGROUNDS_API AInfiniteTerrainGameMode : public ATL4_TestingGroundsGameMode
{
	GENERATED_BODY()
	
public:
	AInfiniteTerrainGameMode();

	UFUNCTION(BlueprintCallable, Category = "Pool")
	void PopulateBoundsVolumePool();
	
	UFUNCTION(BlueprintCallable, Category = "Score")
	void NewTileConquered();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pool")
	class UActorPool* NavMeshBoundsVolumePool;

	UPROPERTY(BlueprintReadOnly, Category = "Score")
	int32 Score;

private:
	void AddToPool(class ANavMeshBoundsVolume* VolumeToAdd);

};
