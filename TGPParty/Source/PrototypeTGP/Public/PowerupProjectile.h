// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Powerup.h"

#include "PowerupProjectile.generated.h"

class UStaticMeshComponent;
class USphereComponent;
class USceneComponent;

UCLASS()
class PROTOTYPETGP_API APowerupProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APowerupProjectile();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Sets the power-up stored in this projectile.
	void SetPowerup(const FPowerup& Powerup);

	// Returns the power-up stored in this projectile.
	UFUNCTION(BlueprintPure)
	FPowerup GetPowerup() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USceneComponent* DefaultRoot = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* Mesh = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USphereComponent* EffectTrigger = nullptr;

private:
	FPowerup PowerupData;
};
