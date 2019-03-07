// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "StatModifier.h"
#include "Powerup.h"

#include "StatModifierComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROTOTYPETGP_API UStatModifierComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UStatModifierComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Applies a power-up.
	UFUNCTION(BlueprintCallable)
	void ApplyPowerup(const FPowerup& PowerupToApply);

	// Returns true if the given modifier is active.
	UFUNCTION(BlueprintPure)
	bool IsModifierActive(EModifierType Type) const;

	// Returns the current amount of the given modifier.
	UFUNCTION(BlueprintPure)
	float GetModifierAmount(EModifierType Type) const;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void ApplyModiferChange(bool& bIsToChangeActive, FStatModifier& ToChange, const FStatModifier& Other);
	void TickModifierTimer(bool& bIsModifierActive, FStatModifier& Modifier, float DeltaTime);

private:
	FStatModifier SpeedModifier;
	FStatModifier SlownessModifier;
	FStatModifier StunModifier;
	FStatModifier ForcePullModifier;
	FStatModifier ForcePushModifier;
	FStatModifier VisibilityModifier;
	FStatModifier ReverseModifier;
	FStatModifier InvulerabilityModifier;

	bool bSpeedModifierActive = false;
	bool bSlownessModifierActive = false;
	bool bStunModifierActive = false;
	bool bForcePullModifierActive = false;
	bool bForcePushModifierActive = false;
	bool bVisibilityModifierActive = false;
	bool bReverseModifierActive = false;
	bool bInvulnerabilityModifierActive = false;
};
