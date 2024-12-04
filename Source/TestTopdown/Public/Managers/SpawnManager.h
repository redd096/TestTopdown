// Copyright redd096. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnManagerComponents/ESpawnManagerState.h"
#include "SpawnManagerComponents/Spawn.h"
#include "SpawnManager.generated.h"

UCLASS()
class TESTTOPDOWN_API ASpawnManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//vars in inspector
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RD | SpawnManager")
	TArray<ASpawn*> Spawns;

	//other vars
	UPROPERTY(BlueprintReadWrite, Category = "RD | SpawnManager")
	ESpawnManagerState State = ESpawnManagerState::None;


	UPROPERTY()
	TArray<AActor*> SpawnedActors;

	UPROPERTY()
	float SpawnTime = 0.0f;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
