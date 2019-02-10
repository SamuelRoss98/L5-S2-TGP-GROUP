// Fill out your copyright notice in the Description page of Project Settings.

#include "FortuneFrenzyPlayer.h"

#include "Components/StaticMeshComponent.h"

// Sets default values
AFortuneFrenzyPlayer::AFortuneFrenzyPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");

	RootComponent = Mesh;
}

// Called when the game starts or when spawned
void AFortuneFrenzyPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

void AFortuneFrenzyPlayer::UpdateMovement()
{
	if (Mesh == nullptr)
	{
		return;
	}

	FVector MovementDirection = FVector(MoveAxisVertical, MoveAxisHorizontal, 0.0f);
	FVector LookDirection = GetActorForwardVector();

	if (LookAxisHorizontal != 0.0f || LookAxisVertical != 0.0f)
	{
		LookDirection = FVector(LookAxisHorizontal, LookAxisVertical, 0.0f);
	}
	else
	{
		if (MoveAxisHorizontal != 0.0f || MoveAxisVertical != 0.0f)
		{
			LookDirection = FVector(MoveAxisHorizontal, -MoveAxisVertical, 0.0f);
		}
	}

	SetActorRotation(LookDirection.Rotation());
	Mesh->AddForce(MovementDirection * BaseMovementForce);
}

// Called every frame
void AFortuneFrenzyPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateMovement();
}

// Called to bind functionality to input
void AFortuneFrenzyPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AFortuneFrenzyPlayer::SetLookAxisHorizontal(float Value)
{
	LookAxisHorizontal = Value;
}

void AFortuneFrenzyPlayer::SetLookAxisVertical(float Value)
{
	LookAxisVertical = Value;
}

void AFortuneFrenzyPlayer::SetMoveAxisHorizontal(float Value)
{
	MoveAxisHorizontal = Value;
}

void AFortuneFrenzyPlayer::SetMoveAxisVertical(float Value)
{
	MoveAxisVertical = Value;
}
