// Copyright redd096. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Characters/RDCharacter.h"
#include "Managers/SpawnManagerComponents/ISpawnable.h"
#include "RDEnemyCharacter.generated.h"

/**
 * Class for every enemy in game
 */
UCLASS()
class TESTTOPDOWN_API ARDEnemyCharacter : public ARDCharacter, public IISpawnable
{
	GENERATED_BODY()

public:
	
	UPROPERTY(BlueprintReadOnly, Category = "RD | Spawn")
	ASpawn* OwnerSpawn;
	
	virtual void InitializeOnSpawn_Implementation(ASpawn* InSpawn) override;
	virtual void DeinitializeOnDespawn_Implementation() override;
};
