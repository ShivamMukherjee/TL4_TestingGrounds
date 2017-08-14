// Copyright (c) Shivam Mukherjee 2017

#include "TL4_TestingGrounds.h"
#include "ChooseNextWaypoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "PatrolRoute.h"


EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory)
{
	UBlackboardComponent* BlackboardComponent = OwnerComponent.GetBlackboardComponent();
	APawn* ControlledPawn = OwnerComponent.GetAIOwner()->GetPawn();
	UPatrolRoute* PatrolRoute = ControlledPawn->FindComponentByClass<UPatrolRoute>();
	
	if (!ensure(BlackboardComponent && PatrolRoute))
	{
		return EBTNodeResult::Failed;
	}

	/// Gets cntrol points
	int32 Index = BlackboardComponent->GetValueAsInt(this->IndexKey.SelectedKeyName);
	TArray<AActor*> PatrolPoints = PatrolRoute->GetPatrolPoints();

	if (PatrolPoints.Num() == 0)
	{
		///UE_LOG(LogTestingGrounds, Warning, TEXT("No patrol routes assigned on %s."), *ControlledPawn->GetName());
		return EBTNodeResult::Failed;
	}

	/// Sets next waypoint and cycles through the patrol points array
	BlackboardComponent->SetValueAsObject(this->Waypoint.SelectedKeyName, PatrolPoints[Index]);
	BlackboardComponent->SetValueAsInt(this->IndexKey.SelectedKeyName, (++Index) % PatrolPoints.Num());

	return EBTNodeResult::Succeeded;
}

