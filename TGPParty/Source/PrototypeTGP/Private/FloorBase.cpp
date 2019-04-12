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
	Selected = false;
	ShakeAmount = 100.f;
}

// Called every frame
void AFloorBase::Tick(float DeltaTime)
{
	// If the floor has been chosen to be changed, then move off screen.
	if (MoveOffScreen)
	{
		MoveOutOfPlay(DeltaTime);
	}

	// If the floor has been chosen to be changed, then move on screen.
	if (MoveOnScreen)
	{
		MoveIntoPlay(DeltaTime);
	}

	// Shakes the floor if its about to move away.
	if(Selected)
	{
		Shake(DeltaTime);
	}
}

void AFloorBase::SetFloorPosition(FVector newPosition)
{
	SetActorLocation(newPosition);

	// Set the floors movement based on its new position.
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

void AFloorBase::MoveOutOfPlay(float DeltaTime)
{
	FVector Position = GetActorLocation();

	Position.Y += YMovement * DeltaTime; // *1.2;
	Position.X += XMovement * DeltaTime; // *1.2;
	Position.Z += 100.f * DeltaTime;

	SetActorLocation(Position);

	// Check to see if floor is far enough of screen to hide.
	if (Position.Y >= 4000.0f || Position.Y <= -4000.0f ||
		Position.X >= 4000.0f || Position.X <= -4000.0f)
	{
		MoveOffScreen = false;
		SetActorLocation(FVector(2500.f, 2500.f, -2500.f));
	}
}

void AFloorBase::MoveIntoPlay(float DeltaTime)
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

	if (Position.Z < 0.f)
	{
		Position.Z += 200.f * DeltaTime;
	}
	else if (Position.Z > 0)
	{
		Position.Z = 0.f;
	}

	SetActorLocation(Position);

	// If floor is in position then stop it.
	if (Position.Y == Destination.Y && Position.X == Destination.X && Position.Z == 0.f)
	{
		MoveOnScreen = false;
	}
}

void AFloorBase::BeginShake()
{
	Selected = true;
	CurrentPosition = GetActorLocation();
}

void AFloorBase::Shake(float DeltaTime)
{
	FVector Position = GetActorLocation();

	Position.X += ShakeAmount * DeltaTime;
	Position.Y += ShakeAmount * DeltaTime;

	if (Position.X > (CurrentPosition.X + (ShakeAmount / 10.f)) && Position.Y > (CurrentPosition.Y + (ShakeAmount / 10.f)))
	{
		ShakeAmount *= -1.f;
		SetActorLocation(CurrentPosition);
	}
	else if (Position.X < (CurrentPosition.X - (ShakeAmount / 10.f)) && Position.Y < (CurrentPosition.Y - (ShakeAmount / 10.f)))
	{
		ShakeAmount *= -1.f;
		SetActorLocation(CurrentPosition);
	}
	else
	{
		SetActorLocation(Position);
	}
}

void AFloorBase::EndShake()
{
	Selected = false;
	SetActorLocation(CurrentPosition);
}

void AFloorBase::SetRandomRotation(int32 random)
{
	FRotator NewRotation = FRotator(0.f, random * 90.f, 0.f);
	SetActorRotation(NewRotation);
}