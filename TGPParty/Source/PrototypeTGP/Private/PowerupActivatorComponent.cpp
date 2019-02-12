// Fill out your copyright notice in the Description page of Project Settings.

#include "PowerupActivatorComponent.h"

#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "FortuneFrenzyPlayer.h"
#include "FortuneFrenzyGameMode.h"

UPowerupActivatorComponent::UPowerupActivatorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UPowerupActivatorComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

}


void UPowerupActivatorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

	if (bPowerupInUse)
	{
		HoldTimer += DeltaTime;

		if (HoldTimer >= SelfCastHoldTimeLimit && !bProjectileMode)
		{
			ActivateProjectileMode();
		}

		if (bProjectileMode)
		{
			DrawDebugLine(GetWorld(), GetOwner()->GetActorLocation(), GetOwner()->GetActorLocation() + GetOwner()->GetActorForwardVector() * 1000.0f, FColor::Red, true, 0.1f, 0, 10.0f);
		}
	}

	// Timer for the primary power-up selection wheel.
	if (bHasPrimaryPowerup && !bPrimaryPowerupReadyToUse)
	{
		PrimarySelectionTimer += DeltaTime;
		if (PrimarySelectionTimer >= PowerWheelTimer)
		{
			bPrimaryPowerupReadyToUse = true;
			RefreshUI();
		}
	}

	// Timer for the secondary power-up selection wheel.
	if (bHasSecondaryPowerup && !bSecondaryPowerupReadyToUse)
	{
		SecondarySelectionTimer += DeltaTime;
		if (SecondarySelectionTimer >= PowerWheelTimer)
		{
			bSecondaryPowerupReadyToUse = true;
			RefreshUI();
		}
	}
}


void UPowerupActivatorComponent::UsePrimaryPowerupPressed()
{
	if (bPowerupInUse)
	{
		return;
	}

	bPrimaryInUse = true;
	StartUseTimer();
}


void UPowerupActivatorComponent::UsePrimaryPowerupReleased()
{
	if (!bPrimaryInUse || !bPowerupInUse)
	{
		return;
	}


	CastPowerup(true);
}


void UPowerupActivatorComponent::UseSecondaryPowerupPressed()
{
	if (bPowerupInUse)
	{
		return;
	}

	bPrimaryInUse = false;
	StartUseTimer();
}


void UPowerupActivatorComponent::UseSecondaryPowerupReleased()
{
	if (bPrimaryInUse || !bPowerupInUse)
	{
		return;
	}

	CastPowerup(false);
}

void UPowerupActivatorComponent::PickupPowerup()
{
	// If both power-up slots are full, exit.
	if (bHasPrimaryPowerup && bHasSecondaryPowerup)
	{
		return;
	}

	if (!bHasPrimaryPowerup)
	{
		GetRandomPowerup(PrimaryPowerup);
		bHasPrimaryPowerup = true;
		bPrimaryPowerupReadyToUse = false;
		PrimarySelectionTimer = 0.0f;
		RefreshUI();
		return;
	}

	if (!bHasSecondaryPowerup)
	{
		GetRandomPowerup(SecondaryPowerup);
		bHasSecondaryPowerup = true;
		bSecondaryPowerupReadyToUse = false;
		SecondarySelectionTimer = 0.0f;
		RefreshUI();
		return;
	}
}

UMaterial * UPowerupActivatorComponent::GetPrimaryPowerupMaterial() const
{
	if (!bHasPrimaryPowerup)
	{
		return PowerupNoneMaterial;
	}

	if (!bPrimaryPowerupReadyToUse)
	{
		return PowerupWheelMaterial;
	}

	return PrimaryPowerup.Icon;
}

UMaterial * UPowerupActivatorComponent::GetSecondaryPowerupMaterial() const
{
	if (!bHasSecondaryPowerup)
	{
		return PowerupNoneMaterial;
	}

	if (!bSecondaryPowerupReadyToUse)
	{
		return PowerupWheelMaterial;
	}

	return SecondaryPowerup.Icon;
}


void UPowerupActivatorComponent::StartUseTimer()
{
	bPowerupInUse = true;
	HoldTimer = 0.0f;
}


void UPowerupActivatorComponent::ActivateProjectileMode()
{
	bProjectileMode = true;

	AFortuneFrenzyPlayer* Owner = Cast<AFortuneFrenzyPlayer>(GetOwner());
	if (Owner == nullptr)
	{
		return;
	}
	Owner->OnStartAiming();
}


void UPowerupActivatorComponent::CastPowerup(bool bPrimary)
{
	if (bProjectileMode)
	{
		ProjectileCast(bPrimary);
	}

	else
	{
		SelfCast(bPrimary);
	}

	bPowerupInUse = false;
	bProjectileMode = false;

	if (bPrimary)
	{
		bHasPrimaryPowerup = false;
		bPrimaryPowerupReadyToUse = false;
	}
	else
	{
		bHasSecondaryPowerup = false;
		bSecondaryPowerupReadyToUse = false;
	}

	RefreshUI();
}


void UPowerupActivatorComponent::SelfCast(bool bPrimary)
{
	AFortuneFrenzyPlayer* Owner = Cast<AFortuneFrenzyPlayer>(GetOwner());
	if (Owner == nullptr)
	{
		return;
	}

	// Primary power.
	if (bPrimary)
	{
		if (!bHasPrimaryPowerup)
		{
			return;
		}

		Owner->ApplyPowerup(PrimaryPowerup);
	}

	// Secondary power.
	else
	{
		if (!bHasSecondaryPowerup)
		{
			return;
		}

		Owner->ApplyPowerup(SecondaryPowerup);
	}

	UE_LOG(LogTemp, Warning, TEXT("Power-up self-cast."))
}


void UPowerupActivatorComponent::ProjectileCast(bool bPrimary)
{
	UE_LOG(LogTemp, Warning, TEXT("Power-up projectile cast."))

	AFortuneFrenzyPlayer* Owner = Cast<AFortuneFrenzyPlayer>(GetOwner());
	if (Owner == nullptr)
	{
		return;
	}
	Owner->OnStopAiming();
}


void UPowerupActivatorComponent::RefreshUI()
{
	AFortuneFrenzyGameMode * FortuneFrenzyGameMode = Cast<AFortuneFrenzyGameMode>(GetWorld()->GetAuthGameMode());
	if (FortuneFrenzyGameMode != nullptr)
	{
		FortuneFrenzyGameMode->UpdatePowerupUI();
		UE_LOG(LogTemp, Warning, TEXT("Called"))
	}
}

void UPowerupActivatorComponent::GetRandomPowerup(FPowerup & outPower)
{
	if (PowerupData == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("PoweripActivatorComponent:GetRandomPowerup - power-up data table not assigned"))
		return;
	}
	TArray<FPowerup*> outItems;
	PowerupData->GetAllRows<FPowerup>("GENERAL", outItems);

	int randomIndex = FMath::RandRange(0, outItems.Num());
	outPower = *outItems[randomIndex];
}
