// Copyright redd096. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Spawn.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSpawn, const AActor*, SpawnedActor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDespawn, const AActor*, DespawnedActor);

UCLASS()
class TESTTOPDOWN_API ASpawn : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawn();

	UPROPERTY(BlueprintAssignable, Category = "RD | Spawn")
	FOnSpawn OnSpawn;

	UPROPERTY(BlueprintAssignable, Category = "RD | Spawn")
	FOnDespawn OnDespawn;

	UFUNCTION(Blueprintable, Category = "RD | Spawn")
	void SpawnActor(const TSubclassOf<AActor>& InActorToSpawn);
};
