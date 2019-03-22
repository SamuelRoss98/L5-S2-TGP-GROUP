// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PowerupSpawner.generated.h"

class UStaticMeshComponent;
class USceneComponent;
class ABaseSpawnedObject;

UCLASS()
class PROTOTYPETGP_API APowerupSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APowerupSpawner();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called when the current spawned object is collected.
	void SpawnedObjectCollected();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Blueprint event triggered when a new power-up spawns.
	UFUNCTION(BlueprintImplementableEvent)
	void OnPowerupSpawn();

	// Blueprint event triggered when a player collects the power-up owned by this spawner.
	UFUNCTION(BlueprintImplementableEvent)
	void OnPowerupCollected();

private:
	// Spawns a power-up.
	void SpawnPowerup();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* Mesh = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USceneComponent* SpawnTransform = nullptr;

	// Power-up actors that will be spawned.
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ABaseSpawnedObject> PowerupClass;

	UPROPERTY(EditDefaultsOnly)
	float TimeBetweenPowerups = 12.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bHasPowerup = false;

private:
	// Time remaining till next spawn.
	float SpawnTimer = TimeBetweenPowerups;
};
