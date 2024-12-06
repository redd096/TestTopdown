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

	//start spawn
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RD | Start Spawn")
	float StartDelay = 2.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RD | Start Spawn", meta = (MustImplement = "ISpawnable"))
	TArray<TSubclassOf<AActor>> StartActorsToSpawn;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RD | Start Spawn")
	int32 StartNumberOfActorsToSpawn = 10;
	
	//game spawn
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RD | Game Spawn")
	float DelayBetweenSpawns = 15.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RD | Game Spawn", meta = (MustImplement = "ISpawnable"))
	TArray<TSubclassOf<AActor>> ActorsToSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RD | Game Spawn")
	float MinDistanceSpawnFromPlayerToSpawn = 300.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RD | Game Spawn")
	int32 ActorsToHaveInSceneNearPlayers = 10;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RD | Game Spawn")
	int32 ActorsToHaveInSceneFarFromPlayers = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RD | Game Spawn")
	float MaxDistanceToEnsureSpawnedActorIsNearPlayers = 1000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RD | Game Spawn")
	float MinDistanceToEnsureSpawnedActorIsFarFromPlayers = 1500.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RD | Game Spawn")
	float TimerBeforeRespawnDeadActor = 15.0f;

	//other vars
	UPROPERTY(BlueprintReadWrite, Category = "RD | SpawnManager")
	ESpawnManagerState State = ESpawnManagerState::None;

	//start spawn
	UPROPERTY(BlueprintReadOnly, Category = "RD | Start Spawn")
	int32 StartSpawnedActors = 0;

	//game spawn
	UPROPERTY(BlueprintReadOnly, Category = "RD | Game Spawn")
	TArray<const AActor*> SpawnedActors;

	UPROPERTY(BlueprintReadOnly, Category = "RD | Game Spawn")
	float SpawnTime = 0.0f;
	
	UPROPERTY(BlueprintReadOnly, Category = "RD | SpawnManager")
	TArray<AActor*> PlayersInScene;

	//functions	
	UFUNCTION(BlueprintCallable, Category = "RD | SpawnManager")
	bool CheckDelay(const float InDelay);
	
	UFUNCTION(BlueprintCallable, Category = "RD | SpawnManager")
	void SpawnActor(const TArray<TSubclassOf<AActor>> InPossibleActors, TArray<ASpawn*> InPossibleSpawns);
	
	UFUNCTION(BlueprintCallable, Category = "RD | SpawnManager")
	void UpdatePlayersInScene();

	UFUNCTION(BlueprintCallable, Category = "RD | SpawnManager")
	float GetDistanceToNearestPlayer(const AActor* InActorToCheck);

	UFUNCTION(BlueprintCallable, Category = "RD | SpawnManager")
	void OnActorSpawn(const AActor* SpawnedActor);

	UFUNCTION(BlueprintCallable, Category = "RD | SpawnManager")
	void OnActorDespawnWithDelay(const AActor* DespawnedActor);

	UFUNCTION(BlueprintCallable, Category = "RD | SpawnManager")
	void OnActorDespawn(const AActor* DespawnedActor);

public:
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "RD | SpawnManager")
	TArray<ASpawn*> GetSpawns() const;
	
	UFUNCTION(BlueprintCallable, Category = "RD | SpawnManager")
	void SetSpawns(TArray<ASpawn*> InSpawns);
};
