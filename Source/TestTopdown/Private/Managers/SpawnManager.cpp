// Copyright redd096. All Rights Reserved.


#include "Managers/SpawnManager.h"

#include "GameFramework/GameStateBase.h"
#include "GameFramework/PlayerState.h"
#include "Kismet/GameplayStatics.h"

ASpawnManager::ASpawnManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ASpawnManager::BeginPlay()
{
	Super::BeginPlay();

	//set default state
	State = ESpawnManagerState::StartSpawn;
	StartSpawnedActors = 0;

	//register to spawners events
	for (const auto Spawn : Spawns)
	{
		Spawn->OnSpawn.AddDynamic(this, &ASpawnManager::OnActorSpawn);
		Spawn->OnDespawn.AddDynamic(this, &ASpawnManager::OnActorDespawnWithDelay);
	}
}

void ASpawnManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//use initial delay to spawn initial mobs
	if (State == ESpawnManagerState::StartSpawn)
	{
		if (CheckDelay(StartDelay))
		{
			SpawnActor(StartActorsToSpawn, Spawns);

			//when reach number, change state
			StartSpawnedActors++;
			if (StartSpawnedActors >= StartNumberOfActorsToSpawn)
				State = ESpawnManagerState::InGame;
		}
	}
	//use in game delay to spawn mobs
	else if (State == ESpawnManagerState::InGame)
	{
		if (CheckDelay(DelayBetweenSpawns))
		{
			//update list of players
			UpdatePlayersInScene();

			//calculate actors near and far from players
			const TArray<const AActor*> ActorsNearPlayers = SpawnedActors.FilterByPredicate([this](const AActor* ActorToCheck)
			{
				return GetDistanceToNearestPlayer(ActorToCheck) < MaxDistanceToEnsureSpawnedActorIsNearPlayers;
			});
			const int32 NumberOfActorsNearPlayers = ActorsNearPlayers.Num();
			const int32 NumberOfActorsFarFromPlayers = SpawnedActors.Num() - NumberOfActorsNearPlayers;

			//instantiate actors near players
			if (NumberOfActorsNearPlayers < ActorsToHaveInSceneNearPlayers)
			{
				const TArray<ASpawn*> PossibleSpawns = Spawns.FilterByPredicate([this](const ASpawn* Spawn)
				{
					const float Distance = GetDistanceToNearestPlayer(Spawn);
					return Distance > MinDistanceSpawnFromPlayerToSpawn && Distance < MaxDistanceToEnsureSpawnedActorIsNearPlayers;
				});				
				SpawnActor(ActorsToSpawn, PossibleSpawns);				
			}
			//or actors far from players
			else if (NumberOfActorsFarFromPlayers < ActorsToHaveInSceneFarFromPlayers)
			{
				const TArray<ASpawn*> PossibleSpawns = Spawns.FilterByPredicate([this](const ASpawn* Spawn)
				{
					return GetDistanceToNearestPlayer(Spawn) > MinDistanceToEnsureSpawnedActorIsFarFromPlayers;
				});
				SpawnActor(ActorsToSpawn, PossibleSpawns);				
			}
		}
	}
}

//check delay is finished and update it
bool ASpawnManager::CheckDelay(const float InDelay)
{
	const float CurrentTime = GetWorld()->TimeSeconds;
	if (CurrentTime > SpawnTime)
	{
		SpawnTime = CurrentTime + InDelay;
		return true;
	}
	return false;
}

//select a spawn and a class, then tell spawn to instantiate that class
void ASpawnManager::SpawnActor(const TArray<TSubclassOf<AActor>> InPossibleActors, const TArray<ASpawn*> InPossibleSpawns)
{
	const int RandomActorIndex = FMath::RandRange(0, InPossibleActors.Num() - 1);
	const int RandomSpawnIndex = FMath::RandRange(0, InPossibleSpawns.Num() - 1);
	const TSubclassOf<AActor> RandomActor = StartActorsToSpawn[RandomActorIndex];
	Spawns[RandomSpawnIndex]->SpawnActor(RandomActor);
}

//find local or online players in scene
void ASpawnManager::UpdatePlayersInScene()
{
	UWorld* World = GetWorld();
	if (World == nullptr)
		return;

	//clear array
	PlayersInScene.Empty();

	//find local players
	if (World->IsNetMode(NM_Standalone))
	{
		const UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(World);
		if (GameInstance)
		{
			//foreach local player, get player controller then player actor
			const TArray<ULocalPlayer*> LocalPlayers = GameInstance->GetLocalPlayers();
			for (const auto LocalPlayer : LocalPlayers)
			{
				const APlayerController* PlayerController = LocalPlayer ? LocalPlayer->PlayerController : nullptr;
				if (PlayerController)
				{
					if (PlayerController->GetPawn())
						PlayersInScene.Add(PlayerController->GetPawn());
				}
			}
		}
	}
	//find online players
	else
	{
		//only if this is the server
		if (HasAuthority())
		{			
			const AGameStateBase* GameState = GetWorld()->GetGameState();
			if (GameState)
			{
				//foreach player state, get player controller then player actor
				const TArray<APlayerState*> PlayerStates = GameState->PlayerArray;
				for (const auto PlayerState : PlayerStates)
				{
					const APlayerController* PlayerController = PlayerState ? PlayerState->GetPlayerController() : nullptr;
					if (PlayerController)
					{
						if (PlayerController->GetPawn())
							PlayersInScene.Add(PlayerController->GetPawn());
					}
				}
			}
		}
	}
}

//check distance from players
float ASpawnManager::GetDistanceToNearestPlayer(const AActor* InActorToCheck)
{
	float MinDistance = FLT_MAX;
	for (const auto PlayerInScene : PlayersInScene)
	{
		const float NewDistance = InActorToCheck->GetDistanceTo(PlayerInScene);
		if (NewDistance < MinDistance)
		{
			MinDistance = NewDistance;
		}
	}
	
	return MinDistance;
}

//add actor to the list
void ASpawnManager::OnActorSpawn(const AActor* SpawnedActor)
{
	SpawnedActors.Add(SpawnedActor);
}

//wait few seconds, then remove actor from the list
void ASpawnManager::OnActorDespawnWithDelay(const AActor* DespawnedActor)
{
	FTimerHandle TimerHandle;
	FTimerDelegate TimerDelegate;
	TimerDelegate.BindUObject(this, &ASpawnManager::OnActorDespawn, DespawnedActor);
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, TimerBeforeRespawnDeadActor, false);
}

//remove actor from the list
void ASpawnManager::OnActorDespawn(const AActor* DespawnedActor)
{
	SpawnedActors.Remove(DespawnedActor);
}

//get Spawns list
TArray<ASpawn*> ASpawnManager::GetSpawns() const
{
	return Spawns;
}

//set Spawns list
void ASpawnManager::SetSpawns(TArray<ASpawn*> InSpawns)
{
	Spawns = InSpawns;
}
