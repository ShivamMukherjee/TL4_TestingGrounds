// Copyright (c) Shivam Mukherjee 2017

#include "TL4_TestingGrounds.h"
#include "GameFramework/Actor.h"
#include "ActorPool.h"


// Sets default values for this component's properties
UActorPool::UActorPool()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


AActor* UActorPool::Checkout()
{
	UE_LOG(LogTestingGrounds, Warning, TEXT("[%s] Checkout."), *GetName());

	if (Pool.Num() == 0)
	{
		return nullptr;
	}

	return Pool.Pop();
}


void UActorPool::Return(AActor* ToReturn)
{
	Add(ToReturn);
}


void UActorPool::Add(AActor* ToAdd)
{
	Pool.Push(ToAdd);
}
