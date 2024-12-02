// Copyright redd096. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "RDCharacter.generated.h"

/**
 * Default class for every Character, both Player and AI. (e.g. to set HealthComponent, WeaponComponent, etc...)
 */
UCLASS(Blueprintable)
class TESTTOPDOWN_API ARDCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ARDCharacter();

// protected:
// 	//Called when the game starts or when spawned
// 	virtual void BeginPlay() override;

// public:	
// 	// Called every frame
// 	virtual void Tick(float DeltaTime) override;
//
// 	// Called to bind functionality to input
// 	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
