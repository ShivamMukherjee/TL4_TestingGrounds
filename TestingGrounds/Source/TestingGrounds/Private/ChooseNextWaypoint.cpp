// Fill out your copyright notice in the Description page of Project Settings.

#include "TestingGrounds.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Public/TP_PatrolGuard.h"
#include "Public/ChooseNextWaypoint.h"


EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory)
{
	UBlackboardComponent* BlackboardComponent = OwnerComponent.GetBlackboardComponent();
	ATP_PatrolGuard* PatrolGuard = Cast<ATP_PatrolGuard>(OwnerComponent.GetAIOwner()->GetPawn());
	
	if (!ensure(BlackboardComponent && PatrolGuard))
	{
		return EBTNodeResult::Aborted;
	}

	int32 Index = BlackboardComponent->GetValueAsInt(this->IndexKey.SelectedKeyName);
	TArray<AActor*> PatrolPoints = PatrolGuard->PatrolPointsCPP;

	BlackboardComponent->SetValueAsObject(this->Waypoint.SelectedKeyName, PatrolPoints[Index]);
	BlackboardComponent->SetValueAsInt(this->IndexKey.SelectedKeyName, (++Index) % PatrolPoints.Num());

	return EBTNodeResult::Succeeded;
}

