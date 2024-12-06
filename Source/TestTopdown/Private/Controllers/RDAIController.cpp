// Copyright redd096. All Rights Reserved.


#include "Controllers/RDAIController.h"
#include "Perception/AIPerceptionComponent.h"

ARDAIController::ARDAIController()
{
	//add AIPerception component
	AIPerception = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AI Perception"));
}

void ARDAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	//start behavior tree
	RunBehaviorTree(BehaviorTree);
}
