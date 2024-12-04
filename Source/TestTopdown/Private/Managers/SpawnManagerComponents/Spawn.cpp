// Copyright redd096. All Rights Reserved.


#include "Managers/SpawnManagerComponents/Spawn.h"
#include "Components/ArrowComponent.h"

// Sets default values
ASpawn::ASpawn()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//add Arrow component
	UArrowComponent* Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	Arrow->SetupAttachment(RootComponent);
}