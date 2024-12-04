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

	//for an FPS
	// /** Pawn mesh: 1st person view (arms; seen only by self) */
	// UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Mesh, meta = (AllowPrivateAccess = "true"))
	// USkeletalMeshComponent* Mesh1P;
	//
	// /** First person camera */
	// UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	// UCameraComponent* FirstPersonCameraComponent;
	
	// // Set size for collision capsule
	// GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
	// 	
	// // Create a CameraComponent	
	// FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	// FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	// FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	// FirstPersonCameraComponent->bUsePawnControlRotation = true;
	//
	// // Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	// Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	// Mesh1P->SetOnlyOwnerSee(true);
	// Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	// Mesh1P->bCastDynamicShadow = false;
	// Mesh1P->CastShadow = false;
	// Mesh1P->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));
}