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

		Position.Y += YMovement * DeltaTime * 1.2;
		Position.X += XMovement * DeltaTime * 1.2;
		Position.Z -= 300.f * DeltaTime;

		SetActorLocation(Position);

		if (Position.Y >= 2500.0f || Position.Y <= -2500.0f || 
			Position.X >= 2500.0f || Position.X <= -2500.0f)
		{
			MoveOffScreen = false;
			SetActorLocation(FVector(1500.f, 1500.f, -1500.f));
		}
	}

	if (MoveOnScreen)
	{
		FVector Position = GetActorLocation();

		if (MoveUp)
		{
			if (Position.X < Destination.X)
			{
				Position.X -= XMovement * DeltaTime;
			}
			else
			{
				MoveUp = false;
				Position.X = Destination.X;
			}
		}

		if (MoveDown)
		{
			if (Position.X > Destination.X)
			{
				Position.X -= XMovement * DeltaTime;
			}
			else
			{
				MoveDown = false;
				Position.X = Destination.X;
			}
		}

		if (MoveLeft)
		{
			if (Position.Y > Destination.Y)
			{
				Position.Y -= YMovement * DeltaTime;
			}
			else
			{
				MoveLeft = false;
				Position.Y = Destination.Y;
			}
		}

		if (MoveRight)
		{
			if (Position.Y < Destination.Y)
			{
				Position.Y -= YMovement * DeltaTime;
			}
			else
			{
				MoveRight = false;
				Position.Y = Destination.Y;
			}
		}

		if (Position.Z > 0.f)
		{
			Position.Z -= 100.f * DeltaTime;
		}
		else if (Position.Z < -12.f)
		{
			Position.Z = 0.f;
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

	if (newPosition.X > 0.0f)
	{
		MoveDown = true;
	}
	else if (newPosition.X < 0.0f)
	{
		MoveUp = true;
	}
	else
	{
		MoveUp = false;
		MoveDown = false;
	}

	if (newPosition.Y > 0.0f)
	{
		MoveLeft = true;
	}
	else if (newPosition.Y < 0.0f)
	{
		MoveRight = true;
	}
	else
	{
		MoveRight = false;
		MoveLeft = false;
	}
}

void AFloorBase::SetFloorMovement()
{
	float XPos = GetActorLocation().X;
	float YPos = GetActorLocation().Y;

	if (XPos > 0.f)
	{
		XMovement = 600.f;
	}
	else if (XPos < 0.f)
	{
		XMovement = -600.f;
	}
	else
	{
		XMovement = 0.f;
	}

	if (YPos > 0.f)
	{
		YMovement = 600.f;
	}
	else if (YPos < 0.f)
	{
		YMovement = -600.f;
	}
	else
	{
		YMovement = 0.f;
	}
}
