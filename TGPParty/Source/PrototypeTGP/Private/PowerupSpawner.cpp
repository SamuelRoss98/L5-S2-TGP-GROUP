// Fill out your copyright notice in the Description page of Project Settings.

#include "PowerupSpawner.h"

#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Engine/World.h"
#include "BaseSpawnedObject.h"

// Sets default values
APowerupSpawner::APowerupSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SpawnTransform = CreateDefaultSubobject<USceneComponent>("Spawn Transform");

	RootComponent = Mesh;
	SpawnTransform->SetupAttachment(Mesh);
}

// Called when the game starts or when spawned
void APowerupSpawner::BeginPlay()
{
	Super::BeginPlay();

	SpawnPowerup();
}

void APowerupSpawner::SpawnPowerup()
{
	FVector SpawnLocation = SpawnTransform->GetComponentLocation();
	FRotator SpawnRotation = SpawnTransform->GetComponentRotation();
	FActorSpawnParameters SpawnParams = FActorSpawnParameters();

	ABaseSpawnedObject* Powerup = Cast<ABaseSpawnedObject>(GetWorld()->SpawnActor(PowerupClass, &SpawnTransform->GetComponentTransform(), SpawnParams));

	// Spawn success.
	if (Powerup != nullptr)
	{
		Powerup->SetSpawner(this);
		bHasPowerup = true;
	}
}

// Called every frame
void APowerupSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Tick spawn timer.
	if (!bHasPowerup)
	{
		SpawnTimer -= DeltaTime;

		if (SpawnTimer <= 0.0f)
		{
			SpawnPowerup();
		}
	}
}

void APowerupSpawner::SpawnedObjectCollected()
{
	// Reset properties.
	bHasPowerup = false;
	SpawnTimer = TimeBetweenPowerups;

	OnPowerupCollected();
}

