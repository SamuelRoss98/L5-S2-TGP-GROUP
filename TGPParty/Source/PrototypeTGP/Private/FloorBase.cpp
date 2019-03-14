// Fill out your copyright notice in the Description page of Project Settings.

#include "FloorBase.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/World.h"
#include "Engine/GameEngine.h"


// Sets default values
AFloorBase::AFloorBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;
}

// Called when the game starts or when spawned
void AFloorBase::BeginPlay()
{
	Super::BeginPlay();
	SetFloorMovement();

	MoveOffScreen = false;
	MoveOnScreen = false;
}

// Called every frame
void AFloorBase::Tick(float DeltaTime)
{
	//Super::Tick(DeltaTime);

	if (MoveOffScreen)
	{
		FVector Position = GetActorLocation();

		Position.Y += YMovement * DeltaTime;
		Position.X += XMovement * DeltaTime;

		SetActorLocation(Position);

		if (Position.Y >= 2000.0f || Position.Y <= -2000.0f || 
			Position.X >= 1500.0f || Position.X <= -1500.0f)
		{
			MoveOffScreen = false;
			SetActorLocation(FVector(1500.f, 1500.f, -1500.f));
		}
	}

	if (MoveOnScreen)
	{
		FVector Position = GetActorLocation();

		if (Position.X != Destination.X)
		{
			Position.X -= XMovement * DeltaTime;
		}

		if (Position.Y != Destination.Y)
		{
			Position.Y -= YMovement * DeltaTime;
		}

		if (Position.Z > -12.f)
		{
			Position.Z -= 50.f * DeltaTime;
		}
		else if (Position.Z < -12.f)
		{
			Position.Z = -12.f;
		}

		SetActorLocation(Position);

		if (Position.Y += Destination.Y && Position.X != Destination.X)
		{
			MoveOnScreen = true;
		}		
	}
}

void AFloorBase::SetFloorPosition(FVector newPosition)
{
	SetActorLocation(newPosition);
	SetFloorMovement();
}

void AFloorBase::SetGoalPosition(FVector newPosition)
{
	Destination = newPosition;

	MoveOnScreen = true;
}

void AFloorBase::SetFloorMovement()
{
	float XPos = GetActorLocation().X;
	float YPos = GetActorLocation().Y;

	if (XPos > 0.f)
		XMovement = 600.f;
	else if (XPos < 0.f)
		XMovement = -600.f;
	else
		XMovement = 0.f;

	if (YPos > 0.f)
		YMovement = 600.f;
	else if (YPos < 0.f)
		YMovement = -600.f;
	else
		YMovement = 0.f;
}
