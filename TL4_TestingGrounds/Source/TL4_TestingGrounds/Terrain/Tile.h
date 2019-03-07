// Copyright (c) Shivam Mukherjee 2017

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"


USTRUCT()
struct FSpawnPosition
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	FVector Location;

	UPROPERTY()
	float YawRotation;

	UPROPERTY()
	float UniformScale;
};


UCLASS()
class TL4_TESTINGGROUNDS_API ATile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties 
	ATile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UFUNCTION(BlueprintCallable, Category = "Score")
	void UpdateTileConquered();

	bool bIsTileConquered = false;

	UPROPERTY(EditDefaultsOnly, Category = "Navigation")
	FVector NavigationBoundsOffset;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Spawning")
	FVector MinExtent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Spawning")
	FVector MaxExtent;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Spawning")
	void PlaceActors(TSubclassOf<AActor> ToSpawn, int32 MinSpawn = 1, int32 MaxSpawn = 1, float ClearanceRadius = 500, float MinScale = 1, float MaxScale = 1);

	UFUNCTION(BlueprintCallable, Category = "Spawning")
	void PlaceAIPawns(TSubclassOf<APawn> ToSpawn, int32 MinSpawn = 1, int32 MaxSpawn = 1, float ClearanceRadius = 500);
	
	UFUNCTION(BlueprintCallable, Category = "Pool")
	void SetActorPool(class UActorPool* InPool);

private:

	void PositionNavMeshBoundsVolume();

	bool FoundEmptyLocation(FVector& OutLocation, float ClearanceRadius);

	template<class A>
	void RandomlyPlaceActors(const TSubclassOf<A>& ToSpawn, int32 MinSpawn, int32 MaxSpawn, float Radius, float MinScale, float MaxScale);

	void PlaceActor(const TSubclassOf<AActor>& ToSpawn, const FSpawnPosition& SpawnPosition);

	void PlaceActor(const TSubclassOf<APawn>& ToSpawn, const FSpawnPosition& SpawnPosition);

	bool CanSpawnAtLocation(FVector Location, float ClearanceRadius);

	class UActorPool* Pool;

	AActor* NavMeshBoundsVolume;
};
