// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseSpawnedObject.generated.h"

class APowerupSpawner;

UCLASS()
class PROTOTYPETGP_API ABaseSpawnedObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseSpawnedObject();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Sets the APowerupSpawner that spawned this object.
	void SetSpawner(APowerupSpawner* Spawner);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Notifies the spawner parent that this object was collected.
	UFUNCTION(BlueprintCallable)
	void NotifySpawnerOfCollection() const;

private:
	// Spawner that spawn this object.
	APowerupSpawner * SpawnerParent = nullptr;
};
