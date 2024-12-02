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
void ARDPlayerController::MovePawn(const FVector2D& InputValue)
{
	APawn* ControlledPawn = GetPawn();
	if (ControlledPawn != nullptr)
	{
		//get direction vector from control rotation (only Yaw)
		const FRotator Rotation = FRotator(0.f, GetControlRotation().Yaw, 0.f);
		const FVector Right = UKismetMathLibrary::GetRightVector(Rotation);
		const FVector Forward = UKismetMathLibrary::GetForwardVector(Rotation);
		// const FVector Right = FVector(1.0f, 0.0f, 0.0f);
		// const FVector Forward = FVector(0.0f, 1.0f, 0.0f);

		const FVector Direction = (Right *  InputValue.X) + (Forward * InputValue.Y);
		ControlledPawn->AddMovementInput(Direction);
		// ControlledPawn->AddMovementInput(Right, InputValue.X);
		// ControlledPawn->AddMovementInput(Forward, InputValue.Y);
	}
}

//rotate controller using input value (sensitivity * deltaSeconds for gamepad or other devices)
void ARDPlayerController::RotateController(const FVector2D& InputValue, const bool UseSensitivity, const float SensitivityValue)
{
	float DeltaSeconds = GetWorld()->GetDeltaSeconds();
	AddYawInput(UseSensitivity ? InputValue.X * DeltaSeconds * SensitivityValue : InputValue.X);
	AddPitchInput(UseSensitivity ? -InputValue.Y * DeltaSeconds * SensitivityValue : -InputValue.Y);
}

void ARDPlayerController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	
	//save character to re-use in blueprint
	PlayerCharacter = GetPawn<ARDPlayerCharacter>();
}
