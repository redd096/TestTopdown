// Copyright redd096. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_SetMaxWalkSpeed.generated.h"

/**
 * 
 */
UCLASS()
class TESTTOPDOWN_API UBTTask_SetMaxWalkSpeed : public UBTTaskNode
{
	GENERATED_BODY()

public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	virtual void OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RD | Task")
	float NewWalkSpeed = 600.0f;

	UFUNCTION(BlueprintCallable, Category = "RD | Task")
	bool SetMaxWalkSpeed(UBehaviorTreeComponent* OwnerComp, const float InWalkSpeed);

private:
	UPROPERTY()
	float PreviousWalkSpeed = 600.0f;
};
