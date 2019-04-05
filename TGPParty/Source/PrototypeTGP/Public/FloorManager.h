// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FloorManager.generated.h"

UCLASS()
class PROTOTYPETGP_API AFloorManager : public AActor
{
	GENERATED_BODY()
	
public:	
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Mesh;

	// Sets default values for this actor's properties
	AFloorManager();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Effects)
	class UParticleSystem* SmokeEffect;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	void BeginMoveFloor();
	void MoveFloor();

	FTimerHandle GetFloorTimer;
	FTimerHandle MoveFloorTimer;
	TArray<class AFloorBase*> ArrayOfFloors;	
	int32 RandFloorToMove;
	int32 NumberOfFloors;
};
