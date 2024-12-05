// Copyright redd096. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Spawn.h"
#include "UObject/Interface.h"
#include "ISpawnable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, BlueprintType)
class UISpawnable : public UInterface
{
	GENERATED_BODY()
};

/**
 * Interface for every actor to spawn with SpawnManager and Spawn
 */
class TESTTOPDOWN_API IISpawnable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void InitializeOnSpawn(ASpawn* InSpawn);
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void DeinitializeOnDespawn();
};
