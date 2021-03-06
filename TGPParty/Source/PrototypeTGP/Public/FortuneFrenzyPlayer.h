// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

#include "Powerup.h"

#include "FortuneFrenzyPlayer.generated.h"

class UStaticMeshComponent;
class UCapsuleComponent;
class UStatModifierComponent;
class UPowerupActivatorComponent;

UCLASS()
class PROTOTYPETGP_API AFortuneFrenzyPlayer : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AFortuneFrenzyPlayer();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Applies a power-up.
	UFUNCTION(BlueprintCallable)
	void ApplyPowerup(const FPowerup& Powerup, bool bSelfCast);

	// Called when powerup input action is pressed.
	virtual void UsePowerupPressed(bool bPrimary);

	// Called when powerup input action is released.
	virtual void UsePowerupReleased(bool bPrimary);

	// Sets the horizontal look input.
	void SetLookAxisHorizontal(float Value);

	// Sets the vertical look input.
	void SetLookAxisVertical(float Value);

	// Sets the horizontal move input.
	void SetMoveAxisHorizontal(float Value);

	// Sets the vertical move input.
	void SetMoveAxisVertical(float Value);

	// Returns the players power-up activator component.
	UFUNCTION(BlueprintPure)
	UPowerupActivatorComponent* GetPowerupActivator() const;

	// Invoked when the players aims something.
	UFUNCTION(BlueprintImplementableEvent)
	void OnStartAiming();

	// Invoked when the player finishes aiming.
	UFUNCTION(BlueprintImplementableEvent)
	void OnStopAiming();

	// Teleport power-up event.
	UFUNCTION(BlueprintImplementableEvent)
	void Teleport();

	// Spawn clones power-up event.
	UFUNCTION(BlueprintImplementableEvent)
	void SpawnClones();

	// Spawn decoy treasure power-up event.
	UFUNCTION(BlueprintImplementableEvent)
	void SpawnDecoyTreasure();

	// Called when a power-up is activated, or expires.
	UFUNCTION(BlueprintImplementableEvent)
	void PowerupStateChange();

	// Fires the primary power-up as projectile.
	UFUNCTION(BlueprintImplementableEvent)
	void FirePrimaryPowerProjectile();

	// Fires the secondary power-up as projectile.
	UFUNCTION(BlueprintImplementableEvent)
	void FireSecondaryPowerProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Moves the player.
	virtual void UpdateMovement();

	// Updates look direction.
	virtual void UpdateLook();

protected:
	// Player mesh.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* Mesh = nullptr;

	// Power-up activator.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UPowerupActivatorComponent* PowerupActivator = nullptr;

	// Stat modifier.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStatModifierComponent* StatChanges = nullptr;

	// Base movement force.
	UPROPERTY(EditDefaultsOnly)
	float BaseMovementForce = 650000.0f;

private:
	float LookAxisHorizontal = 0.0f;
	float LookAxisVertical = 0.0f;
	float MoveAxisHorizontal = 0.0f;
	float MoveAxisVertical = 0.0f;
};
