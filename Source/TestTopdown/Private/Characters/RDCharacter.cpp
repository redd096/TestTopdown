// Copyright redd096. All Rights Reserved.


#include "Characters/RDCharacter.h"
#include "Components/CapsuleComponent.h"

// Sets default values
ARDCharacter::ARDCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
	
	// Set size for capsule
	GetCapsuleComponent()->InitCapsuleSize(42.0f, 96.0f);
	
	//set is replicated online
	// bReplicates = true;
	
	//add here health, weapon or other components
}

// // Called when the game starts or when spawned
// void ARDCharacter::BeginPlay()
// {
// 	Super::BeginPlay();	
// }
//
// // Called every frame
// void ARDCharacter::Tick(float DeltaTime)
// {
// 	Super::Tick(DeltaTime);
// }
//
// // Called to bind functionality to input
// void ARDCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
// {
// 	Super::SetupPlayerInputComponent(PlayerInputComponent);
// }

