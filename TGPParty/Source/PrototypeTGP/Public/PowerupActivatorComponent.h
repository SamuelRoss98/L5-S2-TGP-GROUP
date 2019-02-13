// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "Powerup.h"
#include "Engine/DataTable.h"

#include "PowerupActivatorComponent.generated.h"

class UMaterial;
class APowerupProjectile;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROTOTYPETGP_API UPowerupActivatorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPowerupActivatorComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Called when the action for using primary powerup is first pressed.
	void UsePrimaryPowerupPressed();

	// Called when the action for using primary powerup is released.
	void UsePrimaryPowerupReleased();

	// Called when the action for using secondary powerup is first pressed.
	void UseSecondaryPowerupPressed();

	// Called when the action for using secondary powerup is released.
	void UseSecondaryPowerupReleased();

	// Called to give the controller a powerup when one is collected.
	UFUNCTION(BlueprintCallable)
	void PickupPowerup();

	UFUNCTION(BlueprintPure)
	UMaterial* GetPrimaryPowerupMaterial() const;

	UFUNCTION(BlueprintPure)
	UMaterial* GetSecondaryPowerupMaterial() const;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

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

	// Refreshes UI.
	void RefreshUI();

	// Assigns a random power-up to the input param.
	void GetRandomPowerup(FPowerup& outPower);

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

	// Material for power-up wheel.
	UPROPERTY(EditDefaultsOnly)
	UMaterial* PowerupWheelMaterial = nullptr;

	// Material for no power-up.
	UPROPERTY(EditDefaultsOnly)
	UMaterial* PowerupNoneMaterial = nullptr;

	// Time it takes for the power-up wheel to spin.
	UPROPERTY(EditDefaultsOnly)
	float PowerWheelTimer = 3.0f;

	// Power-up data table.
	UPROPERTY(EditAnywhere)
	UDataTable* PowerupData = nullptr;

	// Power-up projectile class to spawn from.
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<APowerupProjectile> PowerupProjectileClass = nullptr;

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

	// True when the primary power-up is ready to use.
	bool bPrimaryPowerupReadyToUse = false;

	// True when the secondary power-up is ready to use.
	bool bSecondaryPowerupReadyToUse = false;

	// True while there is a primary power-up to use.
	bool bHasPrimaryPowerup = false;

	// True while there is a secondary power-up to use.
	bool bHasSecondaryPowerup = false;

	// Timers for selection wheel
	float PrimarySelectionTimer = 0.0f;
	float SecondarySelectionTimer = 0.0f;
};
