// Fill out your copyright notice in the Description page of Project Settings.

#include "FloorManager.h"
#include "FloorBase.h"
#include "Components/StaticMeshComponent.h"
#include "EngineUtils.h"
#include "Engine/World.h"
#include "Engine/GameEngine.h"
#include "TimerManager.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AFloorManager::AFloorManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;
}

// Called when the game starts or when spawned
void AFloorManager::BeginPlay()
{
	Super::BeginPlay();
	
	// Getting all floors in the scene and adding them to an array
	for (TActorIterator<AFloorBase> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		AFloorBase* NextFloor = *ActorItr;
		ArrayOfFloors.Add(NextFloor);
	}

	NumberOfFloors = ArrayOfFloors.Num();

	// Getting all floors that are not in play and moving them of screen.
	if (NumberOfFloors > 7)
	{
		for (int i = 8; i < NumberOfFloors; i++)
		{
			ArrayOfFloors[i]->SetActorLocation(FVector(-1500.f, -1500.f, -1500.f));
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("There are not enough floors in the level"));
	}


	GetWorld()->GetTimerManager().SetTimer(MoveFloorTimer, this, &AFloorManager::BeginMoveFloor, 8.f, false);
}

// Called every frame
void AFloorManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AFloorManager::BeginMoveFloor()
{
	// Clear timer and get a random floor on screen to move off screen.
	GetWorld()->GetTimerManager().ClearTimer(GetFloorTimer);
	RandFloorToMove = FMath::RandRange(0, 7);

	ArrayOfFloors[RandFloorToMove]->BeginShake();

	if (SmokeEffect)
	{
		// Spawn a smoke effect at the centre of the floor thats going to move
		UParticleSystemComponent* SmokeComp = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), SmokeEffect, ArrayOfFloors[RandFloorToMove]->GetActorLocation());
	}
	
	// Start timer to move floor
	GetWorld()->GetTimerManager().SetTimer(MoveFloorTimer, this, &AFloorManager::MoveFloor, 2.f, false);
}

void AFloorManager::MoveFloor()
{
	// Clear timer
	GetWorld()->GetTimerManager().ClearTimer(MoveFloorTimer);

	// Get a random floor currently off screen to move on screen
	int32 RandFloorToPlay = FMath::RandRange(8, NumberOfFloors - 1);

	// Get the location of the floor on screen and tell it to move off screen
	ArrayOfFloors[RandFloorToMove]->EndShake();
	FVector Location = ArrayOfFloors[RandFloorToMove]->GetActorLocation();
	ArrayOfFloors[RandFloorToMove]->MoveOffScreen = true;

	// Tell floor to move on screen and set it too a position where it can easily move into frame
	ArrayOfFloors[RandFloorToPlay]->SetFloorPosition(FVector((Location.X * 3), (Location.Y * 3), -400.0f));
	ArrayOfFloors[RandFloorToPlay]->SetGoalPosition(Location);

	// Swap the 2 floors position in the array
	ArrayOfFloors.Swap(RandFloorToMove, RandFloorToPlay);

	// Start the timer to the change a new floor again
	GetWorld()->GetTimerManager().SetTimer(GetFloorTimer, this, &AFloorManager::BeginMoveFloor, 8.f, false);
}