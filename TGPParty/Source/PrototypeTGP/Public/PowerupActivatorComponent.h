// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "Powerup.h"

#include "PowerupActivatorComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROTOTYPETGP_API UPowerupActivatorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPowerupActivatorComponent();

	// Called when the action for using primary powerup is first pressed.
	void UsePrimaryPowerupPressed();

	// Called when the action for using primary powerup is released.
	void UsePrimaryPowerupReleased();

	// Called when the action for using secondary powerup is first pressed.
	void UseSecondaryPowerupPressed();

	// Called when the action for using secondary powerup is released.
	void UseSecondaryPowerupReleased();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	// Starts the powerup useage timers.
	void StartUseTimer();

	// Called when the hold timer goes over the SelfCastHoldTimeLimit to enter projectile mode.
	void ActivateProjectileMode();

	// Casts the power-up.
	void CastPowerup(bool bPrimary);

	// Handles self-casting.
	void SelfCast(bool bPrimary);

	// Handles projectile casting.
	void ProjectileCast(bool bPrimary);

protected:
	// Maximum time (seconds) that powerup input can be held before self-cast switches to projectile.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SelfCastHoldTimeLimit = 0.25f;

	// Data for primary power-up.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FPowerup PrimaryPowerup;

	// Data for secondary power-up.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FPowerup SecondaryPowerup;

private:
	// True while a power-up is being cast/aimed.
	bool bPowerupInUse = false;

	// True if the primary power-up is the power-up being used.
	bool bPrimaryInUse = true;

	// True if the power-up being used is being used as a projectile.
	bool bProjectileMode = false;

	// Times how long the power-up action has been held.
	float HoldTimer = 0.0f;

	// Current aiming direction.
	FVector AimingDirection = FVector::ZeroVector;

	// True while there is a primary power-up to use.
	bool bHasPrimaryPowerup = true;

	// True while there is a secondary power-up to use.
	bool bHasSecondaryPowerup = true;
};
