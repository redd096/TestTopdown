// Copyright redd096. All Rights Reserved.


#include "AI/Tasks/BTTask_FindRandomPatrolPoint.h"

FString UBTTask_FindRandomPatrolPoint::GetStaticDescription() const
{
	return Super::GetStaticDescription();

	// return FString::Printf(TEXT("%s for %.1fs"), *Super::GetStaticDescription(), DurationAttack);
	// return FString::Printf(TEXT("Attack for %.1fs"), DurationAttack);
	// return FString::Printf(TEXT("%s: Test"), *Super::GetStaticDescription());
}

EBTNodeResult::Type UBTTask_FindRandomPatrolPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// return Super::ExecuteTask(OwnerComp, NodeMemory);
	
	const AAIController* OwnerController = OwnerComp.GetAIOwner();
	if (OwnerController != nullptr)
	{
		return EBTNodeResult::Succeeded;
	}
	else
	{
		// UE_LOG(LogTemp, Error, TEXT("UBTTask_FindRandomPatrolPoint::ExecuteTask failed since AIController, Pawn or MovementComponent is missing."));
		UE_VLOG(OwnerComp.GetOwner(), LogBehaviorTree, Error, TEXT("UBTTask_FindRandomPatrolPoint::ExecuteTask failed since AIController, Pawn or MovementComponent is missing."));
		return EBTNodeResult::Failed;
	}
}
