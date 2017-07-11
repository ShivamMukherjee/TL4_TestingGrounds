// Copyright (c) Shivam Mukherjee 2017

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "ChooseNextWaypoint.generated.h"

/**
 * 
 */
UCLASS()
class TL4_TESTINGGROUNDS_API UChooseNextWaypoint : public UBTTaskNode
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, Category = "Blackboard")
	struct FBlackboardKeySelector IndexKey;

	UPROPERTY(EditAnywhere, Category = "Blackboard")
	struct FBlackboardKeySelector Waypoint;

private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory) override;
};
