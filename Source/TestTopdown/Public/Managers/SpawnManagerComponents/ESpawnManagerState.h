// Copyright redd096. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ESpawnManagerState.generated.h"

/**
 * Enum used by SpawnManager
 */
UENUM(BlueprintType)
enum class ESpawnManagerState : uint8
{	
	None = 0 UMETA(DisplayName = "None"),
	StartSpawn = 1 UMETA(DisplayName = "Start spawn"),
	InGame = 2 UMETA(DisplayName = "In game"),
};
