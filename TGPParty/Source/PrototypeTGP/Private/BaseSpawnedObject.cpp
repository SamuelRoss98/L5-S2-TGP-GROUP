// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseSpawnedObject.h"

#include "PowerupSpawner.h"

// Sets default values
ABaseSpawnedObject::ABaseSpawnedObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABaseSpawnedObject::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABaseSpawnedObject::SetSpawner(APowerupSpawner * Spawner)
{
	SpawnerParent = Spawner;
}

void ABaseSpawnedObject::NotifySpawnerOfCollection() const
{
	if (SpawnerParent == nullptr)
	{
		return;
	}

	SpawnerParent->SpawnedObjectCollected();
}

// Called every frame
void ABaseSpawnedObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

