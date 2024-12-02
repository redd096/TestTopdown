// Copyright redd096. All Rights Reserved.


#include "Controllers/RDPlayerController.h"
#include "Characters/RDPlayerCharacter.h"
#include "Kismet/KismetMathLibrary.h"

//return character
ARDPlayerCharacter* ARDPlayerController::GetPlayerCharacter() const
{
	return PlayerCharacter;
}

//set if character is valid, and return it or nullptr
ARDPlayerCharacter* ARDPlayerController::GetPlayerCharacterCheckValid(bool& bIsCharacterValid)
{
	bIsCharacterValid = IsValid(PlayerCharacter) ? true : false;
	return PlayerCharacter;
}

//move pawn
void ARDPlayerController::MoveForward(const float InputValue) const
{
	APawn* ControlledPawn = GetPawn();
	if (ControlledPawn != nullptr)
	{
		//get direction vector from control rotation (only Yaw)
		const FRotator Rotation = FRotator(0.f, GetControlRotation().Yaw, 0.f);
		const FVector Direction = UKismetMathLibrary::GetRightVector(Rotation);

		// const FVector Direction = FVector(0.0f, 1.0f, 0.0f);
		ControlledPawn->AddMovementInput(Direction, InputValue);
	}
}

//move pawn
void ARDPlayerController::MoveRight(const float InputValue) const
{
	APawn* ControlledPawn = GetPawn();
	if (ControlledPawn != nullptr)
	{
		//get direction vector from control rotation (only Yaw)
		const FRotator Rotation = FRotator(0.f, GetControlRotation().Yaw, 0.f);
		const FVector Direction = UKismetMathLibrary::GetRightVector(Rotation);
		
		// const FVector Direction = FVector(1.0f, 0.0f, 0.0f);
		ControlledPawn->AddMovementInput(Direction, InputValue);
	}
}

//rotate controller using input value (sensitivity * deltaSeconds for gamepad or other devices)
void ARDPlayerController::RotateYaw(const float InputValue, const bool UseSensitivity, const float SensitivityValue)
{
	float DeltaSeconds = GetWorld()->GetDeltaSeconds();
	AddYawInput(UseSensitivity ? InputValue * DeltaSeconds * SensitivityValue : InputValue);	
}

//rotate controller using input value (sensitivity * deltaSeconds for gamepad or other devices)
void ARDPlayerController::RotatePitch(const float InputValue, const bool UseSensitivity, const float SensitivityValue)
{
	float DeltaSeconds = GetWorld()->GetDeltaSeconds();
	AddPitchInput(UseSensitivity ? InputValue * DeltaSeconds * SensitivityValue : InputValue);
}

void ARDPlayerController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	
	//save character to re-use in blueprint
	PlayerCharacter = GetPawn<ARDPlayerCharacter>();
}
