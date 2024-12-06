// Copyright redd096. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "RDAIController.generated.h"

/**
 * 
 */
UCLASS()
class TESTTOPDOWN_API ARDAIController : public AAIController
{
	GENERATED_BODY()

public:
	ARDAIController();

protected:
	virtual void OnPossess(APawn* InPawn) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "RD | AI")
	UAIPerceptionComponent* AIPerception;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RD | AI")
	UBehaviorTree* BehaviorTree;
};
