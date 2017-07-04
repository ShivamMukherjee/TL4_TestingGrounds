// Fill out your copyright notice in the Description page of Project Settings.

#include "TestingGrounds.h"
#include "ChooseNextWaypoint.h"


EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory)
{
	UE_LOG(TestingGroundsLog, Warning, TEXT("C++ stuff going on: %s"), TEXT(__FUNCSIG__));
	return EBTNodeResult::Succeeded;
}

