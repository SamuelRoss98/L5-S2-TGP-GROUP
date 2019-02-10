// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "FortuneFrenzyPlayerController.generated.h"

class AFortuneFrenzyPlayer;

/**
 * 
 */
UCLASS()
class PROTOTYPETGP_API AFortuneFrenzyPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Allows the PlayerController to set up custom input bindings.
	virtual void SetupInputComponent() override;

private:
	// Called when action for using primary powerup is pressed.
	void UsePrimaryPowerupPressed();

	// Called when action for using secondary powerup is pressed.
	void UseSecondaryPowerupPressed();

	// Called when action for using primary powerup is released.
	void UsePrimaryPowerupReleased();

	// Called when action for using secondary powerup is released.
	void UseSecondaryPowerupReleased();

	// Sets the controlled players horizontal look.
	void SetLookAxisHorizontal(float Value);

	// Sets the controlled players vertical look.
	void SetLookAxisVertical(float Value);

	// Sets the controlled players horizontal movement.
	void SetMoveAxisHorizontal(float Value);

	// Sets the controlled players vertical movement.
	void SetMoveAxisVertical(float Value);

protected:
	// Player class to instantiate.
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AFortuneFrenzyPlayer> PlayerClass;

	// Player controlled by this controller.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	AFortuneFrenzyPlayer* ControlledPlayer = nullptr;
	
};
