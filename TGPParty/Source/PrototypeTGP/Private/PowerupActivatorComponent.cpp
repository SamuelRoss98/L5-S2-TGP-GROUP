// Fill out your copyright notice in the Description page of Project Settings.

#include "PowerupActivatorComponent.h"

#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "FortuneFrenzyPlayer.h"

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


void UPowerupActivatorComponent::StartUseTimer()
{
	bPowerupInUse = true;
	HoldTimer = 0.0f;
}


void UPowerupActivatorComponent::ActivateProjectileMode()
{
	bProjectileMode = true;
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
}