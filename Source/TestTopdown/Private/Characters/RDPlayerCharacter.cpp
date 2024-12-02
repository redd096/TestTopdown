// Copyright redd096. All Rights Reserved.


#include "Characters/RDPlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

ARDPlayerCharacter::ARDPlayerCharacter()
{	
	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	
	// Configure character movement
	UCharacterMovementComponent* CharMovement = GetCharacterMovement();
	CharMovement->bOrientRotationToMovement = true;			// Rotate character to moving direction
	CharMovement->RotationRate = FRotator(0.0f, 640.f, 0.0f);
	CharMovement->bConstrainToPlane = true;
	CharMovement->bSnapToPlaneAtStart = true;	
	CharMovement->GetNavMovementProperties()->bUseAccelerationForPaths = true;	// Use acceleration also for navmesh

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true);				// Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.0f;
	CameraBoom->SetRelativeRotation(FRotator(-50.0f, 0.0f, 0.0f));
	CameraBoom->bDoCollisionTest = false;					// Don't want to pull camera in when it collides with level
	CameraBoom->bEnableCameraLag = true;					// Camera Lag
	CameraBoom->CameraLagSpeed = 3.0f;

	// Create a camera...
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	CameraComponent->bUsePawnControlRotation = false;		// Camera does not rotate relative to arm
}