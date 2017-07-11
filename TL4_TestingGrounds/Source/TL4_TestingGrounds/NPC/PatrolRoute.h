// Copyright (c) Shivam Mukherjee 2017

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PatrolRoute.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TL4_TESTINGGROUNDS_API UPatrolRoute : public UActorComponent
{
	GENERATED_BODY()

public:
	FORCEINLINE TArray<AActor*> GetPatrolPoints() const
	{
		return this->PatrolPoints;
	}

private:
	UPROPERTY(EditInstanceOnly, Category = "Patrol Route")
	TArray<AActor*> PatrolPoints;
	
};
