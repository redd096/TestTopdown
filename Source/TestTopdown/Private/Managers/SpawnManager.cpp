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

	//register to spawners events
	for (const auto Spawn : Spawns)
	{
		Spawn->OnSpawn.AddDynamic(this, &ASpawnManager::OnActorSpawn);
		Spawn->OnDespawn.AddDynamic(this, &ASpawnManager::OnActorDespawn);
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
			//only if still there isn't the number of actors in scene
			if (SpawnedActors.Num() < ActorsToHaveInScene)
			{
				//only spawners with minimum distance from players
				const TArray<ASpawn*> PossibleSpawns = Spawns.FilterByPredicate([this](const ASpawn* Spawn)
				{
					for (const auto PlayerInScene : PlayersInScene)
					{
						if (Spawn->GetDistanceTo(PlayerInScene) < MinDistanceSpawnFromPlayer)
							return false;
					}
					return true;
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

void ASpawnManager::OnActorSpawn(const AActor* SpawnedActor)
{
	SpawnedActors.Add(SpawnedActor);
}

void ASpawnManager::OnActorDespawn(const AActor* DespawnedActor)
{
	SpawnedActors.Add(DespawnedActor);
}
