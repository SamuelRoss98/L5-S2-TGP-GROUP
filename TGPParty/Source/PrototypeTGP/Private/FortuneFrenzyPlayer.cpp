// Fill out your copyright notice in the Description page of Project Settings.

#include "FortuneFrenzyPlayer.h"

#include "Components/StaticMeshComponent.h"
#include "StatModifierComponent.h"
#include "PowerupActivatorComponent.h"


AFortuneFrenzyPlayer::AFortuneFrenzyPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	StatChanges = CreateDefaultSubobject<UStatModifierComponent>("StatChanges");
	PowerupActivator = CreateDefaultSubobject<UPowerupActivatorComponent>("PowerupActivator");

	if (StatChanges == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Stat is nullptr in construction"))
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Stat is OK is construction"))
	}

	RootComponent = Mesh;
}



void AFortuneFrenzyPlayer::BeginPlay()
{
	Super::BeginPlay();

	if (StatChanges == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Stat is nullptr in begin play"))
	}
}


void AFortuneFrenzyPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (StatChanges == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Stat is nullptr in tick"))
	}

	UpdateMovement();
	UpdateLook();
}


void AFortuneFrenzyPlayer::UpdateMovement()
{
	if (Mesh == nullptr || StatChanges == nullptr)
	{
		return;
	}

	// Can't move while stunned.
	if (StatChanges->IsModifierActive(EModifierType::Stun))
	{
		return;
	}

	float SpeedModifierForce = StatChanges->GetModifierAmount(EModifierType::Speed);
	float SlowModifierForce = StatChanges->GetModifierAmount(EModifierType::Slowness);

	float ForceMagnitude = BaseMovementForce + (SpeedModifierForce - SlowModifierForce);
	if (ForceMagnitude <= 0.0f)
	{
		ForceMagnitude = 0.0f;
	}

	FVector MovementDirection = FVector(MoveAxisVertical, MoveAxisHorizontal, 0.0f);

	// Reverse controls if modifier is active.
	if (StatChanges->IsModifierActive(EModifierType::Reverse))
	{
		MovementDirection *= -1.0f;
	}

	Mesh->AddForce(MovementDirection * ForceMagnitude);
}


void AFortuneFrenzyPlayer::UpdateLook()
{
	if (StatChanges == nullptr)
	{
		return;
	}

	// Can't move while stunned.
	if (StatChanges->IsModifierActive(EModifierType::Stun))
	{
		return;
	}

	FVector MovementDirection = FVector(MoveAxisVertical, MoveAxisHorizontal, 0.0f);
	FVector LookDirection = GetActorForwardVector();

	if (LookAxisHorizontal != 0.0f || LookAxisVertical != 0.0f)
	{
		LookDirection = FVector(-LookAxisVertical, LookAxisHorizontal, 0.0f);
	}
	else
	{
		if (MoveAxisHorizontal != 0.0f || MoveAxisVertical != 0.0f)
		{
			LookDirection = FVector(MoveAxisVertical, MoveAxisHorizontal, 0.0f);
		}
	}
	SetActorRotation(LookDirection.Rotation());
}



void AFortuneFrenzyPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AFortuneFrenzyPlayer::ApplyPowerup(const FPowerup & Powerup)
{
	if (StatChanges == nullptr)
	{
		return;
	}

	StatChanges->ApplyPowerup(Powerup);
}


void AFortuneFrenzyPlayer::UsePowerupPressed(bool bPrimary)
{
	if (PowerupActivator == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Called"))
		return;
	}

	if (bPrimary)
	{
		PowerupActivator->UsePrimaryPowerupPressed();
	}

	else
	{
		PowerupActivator->UseSecondaryPowerupPressed();
	}
}


void AFortuneFrenzyPlayer::UsePowerupReleased(bool bPrimary)
{
	if (PowerupActivator == nullptr)
	{
		return;
	}

	if (bPrimary)
	{
		PowerupActivator->UsePrimaryPowerupReleased();
	}

	else
	{
		PowerupActivator->UseSecondaryPowerupReleased();
	}
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

UPowerupActivatorComponent * AFortuneFrenzyPlayer::GetPowerupActivator() const
{
	return PowerupActivator;
}
