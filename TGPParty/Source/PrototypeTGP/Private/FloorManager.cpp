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

	// Getting all floors that are not in play and moving them of screen.
	for (int i = 8; i < ArrayOfFloors.Num(); i++)
	{
		ArrayOfFloors[i]->SetActorLocation(FVector(-1500.f, -1500.f, -1500.f));
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
	GetWorld()->GetTimerManager().ClearTimer(GetFloorTimer);
	RandFloorToMove = FMath::RandRange(0, 7);

	if (SmokeEffect)
	{
		//Spawn the smoke effect at the centre of the floor thats going to move
		UParticleSystemComponent* SmokeComp = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), SmokeEffect, ArrayOfFloors[RandFloorToMove]->GetActorLocation());
	}
	
	GetWorld()->GetTimerManager().SetTimer(MoveFloorTimer, this, &AFloorManager::MoveFloor, 2.f, false);
}

void AFloorManager::MoveFloor()
{
	GetWorld()->GetTimerManager().ClearTimer(MoveFloorTimer);
	int32 RandFloorToPlay = FMath::RandRange(8, ArrayOfFloors.Num() - 1);
	FVector Location = ArrayOfFloors[RandFloorToMove]->GetActorLocation();

	ArrayOfFloors[RandFloorToMove]->MoveOffScreen = true;
	ArrayOfFloors[RandFloorToPlay]->SetFloorPosition(FVector((Location.X * 3), (Location.Y * 3), 210.0f));
	ArrayOfFloors[RandFloorToPlay]->SetGoalPosition(Location);
	ArrayOfFloors.Swap(RandFloorToMove, RandFloorToPlay);

	GetWorld()->GetTimerManager().SetTimer(GetFloorTimer, this, &AFloorManager::BeginMoveFloor, 8.f, false);
}