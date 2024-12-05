// Copyright redd096. All Rights Reserved.


#include "Managers/SpawnManagerComponents/Spawn.h"
#include "Components/ArrowComponent.h"
#include "Managers/SpawnManagerComponents/ISpawnable.h"

ASpawn::ASpawn()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//add Arrow component
	UArrowComponent* Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	Arrow->SetupAttachment(RootComponent);
}

//instantiate class at position and set path
void ASpawn::SpawnActor(const TSubclassOf<AActor>& InActorToSpawn)
{
	//be sure implement interface
	if (InActorToSpawn == nullptr || InActorToSpawn->ImplementsInterface(UISpawnable::StaticClass()) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("SpawnActor: Interface is null"));
		return;
	}

	//spawn actor and initialize
	const FVector SpawnPosition = GetActorLocation();
	AActor* SpawnedActor = GetWorld()->SpawnActor(InActorToSpawn, &SpawnPosition);
	IISpawnable::Execute_InitializeOnSpawn(SpawnedActor, this);
}
