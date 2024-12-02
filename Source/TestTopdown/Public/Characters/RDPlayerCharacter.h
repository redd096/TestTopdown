// Copyright redd096. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Characters/RDCharacter.h"
#include "RDPlayerCharacter.generated.h"

/**
 * The class for a Character controlled by Player (e.g. to set the camera)
 */
UCLASS(Blueprintable)
class TESTTOPDOWN_API ARDPlayerCharacter : public ARDCharacter
{
	GENERATED_BODY()

public:
	ARDPlayerCharacter();

protected:	
	// Top down camera
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RD | Camera", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* CameraComponent;

	// Camera boom positioning the camera above the character
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RD | Camera", meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;
};
