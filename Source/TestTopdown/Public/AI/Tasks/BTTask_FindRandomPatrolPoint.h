// Copyright redd096. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_FindRandomPatrolPoint.generated.h"

/**
 * 
 */
UCLASS()
class TESTTOPDOWN_API UBTTask_FindRandomPatrolPoint : public UBTTaskNode
{
	GENERATED_BODY()

public:
	//show description in Blueprint BehaviorTree (under the name)
	virtual FString GetStaticDescription() const override;
	
	//starts this task, should return Succeeded, Failed or InProgress
	//NB if return InProgress, in another time should return Succeeded or Failed by call FinishLatentTask(*MyOwnerComp, EBTNodeResult::Succeeded);
	//NB MyOwnerComp is a saved variable of the UBehaviorTreeComponent in this function (MyOwnerComp = &OwnerComp;)
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	//get icon to show in BlueprintBehaviourTree
// #if WITH_EDITOR
// 	virtual FName GetNodeIconName() const override;
// #endif // WITH_EDITOR
	//
	//result in .cpp
// #if WITH_EDITOR
// 	FName UBTTask_MoveTo::GetNodeIconName() const
// 	{
// 		return FName("BTEditor.Graph.BTNode.Task.MoveTo.Icon");
// 	}
// #endif	// WITH_EDITOR

// protected:	
	//aborts this task, should return Aborted or InProgress
	//(use FinishLatentAbort() when returning InProgress)
	// virtual EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	//tick
	// virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	//I think this is called everytime the task is finished, for execute, abort, finishLatentTask or finishLatentAbort
	// virtual void OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult) override;

	//select a key in the blackboard - OwnerComp.GetBlackboardComponent()->SetValueAsBool(BlackboardKeyA.SelectedKeyName, bValueToSet);
	// UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "RD")
	// FBlackboardKeySelector BlackboardKey;
	//
	//to select only specific types add filter in the task constructor, for example select only object and vector:
	// BlackboardKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UBTTask_MoveTo, BlackboardKey), AActor::StaticClass());
	// BlackboardKey.AddVectorFilter(this, GET_MEMBER_NAME_CHECKED(UBTTask_MoveTo, BlackboardKey));
};
