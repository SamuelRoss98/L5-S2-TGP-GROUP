// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FloorBase.generated.h"

UCLASS()
class PROTOTYPETGP_API AFloorBase : public AActor
{
	GENERATED_BODY()
	
public:	
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Mesh;

	// Sets default values for this actor's properties
	AFloorBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetFloorPosition(FVector newPosition);
	void SetGoalPosition(FVector newPosition);

private:
	void SetFloorMovement();

private:
	float XMovement;
	float YMovement;
	bool MoveOnScreen;

	FVector Destination;

public:
	bool MoveOffScreen;
};
