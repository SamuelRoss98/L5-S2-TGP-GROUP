// Fill out your copyright notice in the Description page of Project Settings.

#include "FortuneFrenzyPlayerController.h"

#include "Engine/World.h"
#include "FortuneFrenzyPlayer.h"

void AFortuneFrenzyPlayerController::BeginPlay()
{
	FVector SpawnLocation = FVector::ZeroVector;
	FRotator SpawnRotation = FRotator::ZeroRotator;
	FActorSpawnParameters SpawnParams;
	ControlledPlayer = Cast<AFortuneFrenzyPlayer>(GetWorld()->SpawnActor(PlayerClass, &SpawnLocation, &SpawnRotation, SpawnParams));
	if (ControlledPlayer == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("AFortuneFrenzyPlayerController::BeginPlay - Failed to spawn player."))
	}
}

void AFortuneFrenzyPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (InputComponent != nullptr)
	{
		// Axis bindings.
		InputComponent->BindAxis("LookHorizontal", this, &AFortuneFrenzyPlayerController::SetLookAxisHorizontal);
		InputComponent->BindAxis("LookVertical", this, &AFortuneFrenzyPlayerController::SetLookAxisVertical);
		InputComponent->BindAxis("MoveHorizontal", this, &AFortuneFrenzyPlayerController::SetMoveAxisHorizontal);
		InputComponent->BindAxis("MoveVertical", this, &AFortuneFrenzyPlayerController::SetMoveAxisVertical);

		// Action bindings.
		InputComponent->BindAction("UsePrimaryPowerup", IE_Pressed, this, &AFortuneFrenzyPlayerController::UsePrimaryPowerupPressed);
		InputComponent->BindAction("UseSecondaryPowerup", IE_Pressed, this, &AFortuneFrenzyPlayerController::UseSecondaryPowerupPressed);
		InputComponent->BindAction("UsePrimaryPowerup", IE_Released, this, &AFortuneFrenzyPlayerController::UsePrimaryPowerupReleased);
		InputComponent->BindAction("UseSecondaryPowerup", IE_Released, this, &AFortuneFrenzyPlayerController::UseSecondaryPowerupReleased);

		//InputComponent->BindAction("UsePowerupPrimary", IE_Pressed, this, &APowerupPlayerController::UsePrimaryPowerupPressed);
		//InputComponent->BindAxis("LookVertical", this, &AFortuneFrenzyPlayer::SetLookAxisVertical);*/
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("AFortuneFrenzyPlayerController::SetupInputComponent - InputComponent is nullptr"))
	}
}


void AFortuneFrenzyPlayerController::UsePrimaryPowerupPressed()
{
	if (ControlledPlayer == nullptr)
	{
		return;
	}

	else
	{
		ControlledPlayer->UsePowerupPressed(true);
	}
}


void AFortuneFrenzyPlayerController::UseSecondaryPowerupPressed()
{
	if (ControlledPlayer == nullptr)
	{
		return;
	}
	else
	{
		ControlledPlayer->UsePowerupPressed(false);
	}
}


void AFortuneFrenzyPlayerController::UsePrimaryPowerupReleased()
{
	if (ControlledPlayer == nullptr)
	{
		return;
	}

	ControlledPlayer->UsePowerupReleased(true);
}


void AFortuneFrenzyPlayerController::UseSecondaryPowerupReleased()
{
	if (ControlledPlayer == nullptr)
	{
		return;
	}

	ControlledPlayer->UsePowerupReleased(false);
}


void AFortuneFrenzyPlayerController::SetLookAxisHorizontal(float Value)
{
	if (ControlledPlayer == nullptr)
	{
		return;
	}

	ControlledPlayer->SetLookAxisHorizontal(Value);
}


void AFortuneFrenzyPlayerController::SetLookAxisVertical(float Value)
{
	if (ControlledPlayer == nullptr)
	{
		return;
	}

	ControlledPlayer->SetLookAxisVertical(Value);
}

void AFortuneFrenzyPlayerController::SetMoveAxisHorizontal(float Value)
{
	if (ControlledPlayer == nullptr)
	{
		return;
	}

	ControlledPlayer->SetMoveAxisHorizontal(Value);
}

void AFortuneFrenzyPlayerController::SetMoveAxisVertical(float Value)
{
	if (ControlledPlayer == nullptr)
	{
		return;
	}

	ControlledPlayer->SetMoveAxisVertical(Value);
}


