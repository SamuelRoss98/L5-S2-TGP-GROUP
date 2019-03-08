// Fill out your copyright notice in the Description page of Project Settings.

#include "StatModifierComponent.h"

#include "FortuneFrenzyPlayer.h"

UStatModifierComponent::UStatModifierComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UStatModifierComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

}


void UStatModifierComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

	TickModifierTimer(bSpeedModifierActive, SpeedModifier, DeltaTime);
	TickModifierTimer(bSlownessModifierActive, SlownessModifier, DeltaTime);
	TickModifierTimer(bStunModifierActive, StunModifier, DeltaTime);
	TickModifierTimer(bForcePullModifierActive, ForcePullModifier, DeltaTime);
	TickModifierTimer(bForcePushModifierActive, ForcePushModifier, DeltaTime);
	TickModifierTimer(bVisibilityModifierActive, VisibilityModifier, DeltaTime);
	TickModifierTimer(bReverseModifierActive, ReverseModifier, DeltaTime);
	TickModifierTimer(bInvulnerabilityModifierActive, InvulerabilityModifier, DeltaTime);
}


void UStatModifierComponent::ApplyPowerup(const FPowerup & PowerupToApply)
{
	// If invulerability is active power-ups cannot be applied.
	if (bInvulnerabilityModifierActive)
	{
		return;
	}

	// Call required power-up events.
	AFortuneFrenzyPlayer* Player = Cast<AFortuneFrenzyPlayer>(GetOwner());
	if (Player != nullptr)
	{
		if (PowerupToApply.bSpawnDecoyTreasure)
		{
			Player->SpawnDecoyTreasure();
		}

		if (PowerupToApply.bTeleport)
		{
			Player->Teleport();
		}

		if (PowerupToApply.bSpawnClones)
		{
			Player->SpawnClones();
		}
	}

	// Apply modifiers.
	ApplyModiferChange(bSpeedModifierActive, SpeedModifier, PowerupToApply.SpeedModifier);
	ApplyModiferChange(bSlownessModifierActive, SlownessModifier, PowerupToApply.SlownessModifier);
	ApplyModiferChange(bStunModifierActive, StunModifier, PowerupToApply.StunModifier);
	ApplyModiferChange(bForcePullModifierActive, ForcePullModifier, PowerupToApply.ForcePullModifier);
	ApplyModiferChange(bForcePushModifierActive, ForcePushModifier, PowerupToApply.ForcePushModifier);
	ApplyModiferChange(bVisibilityModifierActive, VisibilityModifier, PowerupToApply.VisibilityModifier);
	ApplyModiferChange(bReverseModifierActive, ReverseModifier, PowerupToApply.ReverseModifier);
	ApplyModiferChange(bInvulnerabilityModifierActive, InvulerabilityModifier, PowerupToApply.InvulnerabilityModifer);
}


bool UStatModifierComponent::IsModifierActive(EModifierType Type) const
{
	switch (Type)
	{
	case EModifierType::Speed:
		return bSpeedModifierActive;
	case EModifierType::Slowness:
		return bSlownessModifierActive;
	case EModifierType::Stun:
		return bStunModifierActive;
	case EModifierType::ForcePush:
		return bForcePushModifierActive;
	case EModifierType::ForcePull:
		return bForcePullModifierActive;
	case EModifierType::Visibility:
		return bVisibilityModifierActive;
	case EModifierType::Reverse:
		return bReverseModifierActive;
	case EModifierType::Invulnerability:
		return bInvulnerabilityModifierActive;
	default:
		UE_LOG(LogTemp, Warning, TEXT("UStatModifierComponent::IsModifierActive - invalid argument."))
			return false;
	}
}


float UStatModifierComponent::GetModifierAmount(EModifierType Type) const
{
	switch (Type)
	{
	case EModifierType::Speed:
		return SpeedModifier.Amount;
	case EModifierType::Slowness:
		return SlownessModifier.Amount;
	case EModifierType::Stun:
		return StunModifier.Amount;
	case EModifierType::ForcePush:
		return ForcePushModifier.Amount;
	case EModifierType::ForcePull:
		return ForcePullModifier.Amount;
	case EModifierType::Visibility:
		return VisibilityModifier.Amount;
	case EModifierType::Reverse:
		return ReverseModifier.Amount;
	case EModifierType::Invulnerability:
		return InvulerabilityModifier.Amount;
	default:
		UE_LOG(LogTemp, Warning, TEXT("UStatModifierComponent::GetModifierAmount - invalid argument."))
			return 0.0f;
	}
}


void UStatModifierComponent::ApplyModiferChange(bool & bIsToChangeActive, FStatModifier & ToChange, const FStatModifier & Other)
{
	// The modifier we are changing isn't active - values can just be applied.
	if (!bIsToChangeActive)
	{
		ToChange.Amount = Other.Amount;
		ToChange.Duration = Other.Duration;
	}

	// As modifier is already active - combination settings are used.
	else
	{
		switch (Other.AmountCombinationMethod)
		{
		case EModifierCombinationMethod::Discard:
			break;
		case EModifierCombinationMethod::Overwrite:
			ToChange.Amount = Other.Amount;
			break;
		case EModifierCombinationMethod::Stack:
			ToChange.Amount += Other.Amount;
		default:
			break;
		}

		switch (Other.DurationCombinationMethod)
		{
		case EModifierCombinationMethod::Discard:
			break;
		case EModifierCombinationMethod::Overwrite:
			ToChange.Duration = Other.Duration;
			break;
		case EModifierCombinationMethod::Stack:
			ToChange.Duration += Other.Duration;
		default:
			break;
		}
	}

	bIsToChangeActive = true;
}


void UStatModifierComponent::TickModifierTimer(bool & bIsModifierActive, FStatModifier & Modifier, float DeltaTime)
{
	if (!bIsModifierActive)
	{
		return;
	}

	Modifier.Duration -= DeltaTime;
	if (Modifier.Duration <= 0.0f)
	{
		Modifier.Duration = 0.0f;
		Modifier.Amount = 0.0f;
		bIsModifierActive = false;
	}
}