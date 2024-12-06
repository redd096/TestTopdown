// Copyright redd096. All Rights Reserved.


#include "AI/Tasks/BTTask_SetMaxWalkSpeed.h"
#include "AIController.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

EBTNodeResult::Type UBTTask_SetMaxWalkSpeed::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// return Super::ExecuteTask(OwnerComp, NodeMemory);

	//set new speed
	if (SetMaxWalkSpeed(&OwnerComp, NewWalkSpeed))
	{
		return EBTNodeResult::Succeeded;
	}
	else
	{		
		// UE_LOG(LogTemp, Error, TEXT("UBTTask_SetMaxWalkSpeed::ExecuteTask failed since AIController, Character or MovementComponent is missing."));
		UE_VLOG(OwnerComp.GetOwner(), LogBehaviorTree, Error, TEXT("UBTTask_SetMaxWalkSpeed::ExecuteTask failed since AIController, Character or MovementComponent is missing."));
		return EBTNodeResult::Failed;
	}
}

void UBTTask_SetMaxWalkSpeed::OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult)
{
	Super::OnTaskFinished(OwnerComp, NodeMemory, TaskResult);

	//set previous speed
	const bool bSucceeded = SetMaxWalkSpeed(&OwnerComp, PreviousWalkSpeed);
	if (bSucceeded == false)
	{		
		// UE_LOG(LogTemp, Error, TEXT("UBTTask_FindRandomPatrolPoint::ExecuteTask failed since AIController, Character or MovementComponent is missing."));
		UE_VLOG(OwnerComp.GetOwner(), LogBehaviorTree, Error, TEXT("UBTTask_SetMaxWalkSpeed::OnTaskFinished failed since AIController, Character or MovementComponent is missing."));
	}
	
}

bool UBTTask_SetMaxWalkSpeed::SetMaxWalkSpeed(UBehaviorTreeComponent* OwnerComp, const float InWalkSpeed)
{
	//find character movement component
	const AAIController* OwnerController = OwnerComp->GetAIOwner();
	if (OwnerController != nullptr)
	{
		const APawn* OwnerPawn = OwnerController->GetPawn();
		if (OwnerPawn != nullptr)
		{
			const ACharacter* OwnerCharacter = Cast<ACharacter>(OwnerPawn);
			if (OwnerCharacter != nullptr)
			{
				UCharacterMovementComponent* OwnerMovementComponent = OwnerCharacter->GetCharacterMovement();
				if (OwnerMovementComponent != nullptr)
				{
					//save previous walk speed and set new walk speed
					PreviousWalkSpeed = OwnerMovementComponent->MaxWalkSpeed;
					OwnerMovementComponent->MaxWalkSpeed = InWalkSpeed;
					return true;
				}
			}
		}
	}

	return false;
}
