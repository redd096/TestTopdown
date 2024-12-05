// Copyright redd096. All Rights Reserved.


#include "Characters/RDEnemyCharacter.h"

//save refs and call event
void ARDEnemyCharacter::InitializeOnSpawn_Implementation(ASpawn* InSpawn)
{
	IISpawnable::InitializeOnSpawn_Implementation(InSpawn);

	OwnerSpawn = InSpawn;
	OwnerSpawn->OnSpawn.Broadcast(this);
}

//call event
void ARDEnemyCharacter::DeinitializeOnDespawn_Implementation()
{
	IISpawnable::DeinitializeOnDespawn_Implementation();

	if (OwnerSpawn != nullptr)
	{
		OwnerSpawn->OnDespawn.Broadcast(this);
	}
}
