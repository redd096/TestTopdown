// Copyright redd096. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "RDPlayerController.generated.h"

/**
 * PlayerController for RDPlayerCharacter
 */
UCLASS()
class TESTTOPDOWN_API ARDPlayerController : public APlayerController
{
	GENERATED_BODY()

private:
	//vars character
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "RD | Character", meta = (AllowPrivateAccess = "true"))
	class ARDPlayerCharacter* PlayerCharacter;

protected:
	//vars inputs
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "RD | Inputs")
	float GamepadSensitivityYaw = 45;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "RD | Inputs")
	float GamepadSensitivityPitch = 45;

	//functions	character
	UFUNCTION(BlueprintPure, Category = "RD | Character")
	ARDPlayerCharacter* GetPlayerCharacter() const;

	//ExpandAsExecs to show multiple Out pin in Blueprint
	UFUNCTION(BlueprintCallable, meta = (ExpandBoolAsExecs = "bIsCharacterValid"), Category = "RD | Character")
	ARDPlayerCharacter* GetPlayerCharacterCheckValid(bool& bIsCharacterValid);

	//functions inputs
	UFUNCTION(BlueprintCallable, Category = "RD | Inputs")
	void MovePawn(const FVector2D& InputValue);
	
	UFUNCTION(BlueprintCallable, Category = "RD | Inputs")
	void RotateController(const FVector2D& InputValue, const bool UseSensitivity = false, const float SensitivityValue = 1);

public:
	virtual void SetPawn(APawn* InPawn) override;
};
