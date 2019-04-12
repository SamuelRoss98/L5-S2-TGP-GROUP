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

	// Sets floor position and calls SetFloorMovement
	void SetFloorPosition(FVector newPosition);

	// Sets the floors target destination
	void SetGoalPosition(FVector newPosition);

	// Called to start or stop a floor shake
	void BeginShake();
	void EndShake();

	// Use random to multiple by 90 to get a new Z/Yaw rotation.
	void SetRandomRotation(int32 random); 

private:
	// Sets floors direction to move off or on screen
	void SetFloorMovement();

	// Use to move floor
	void MoveOutOfPlay(float DeltaTime);
	void MoveIntoPlay(float DeltaTime);
	void Shake(float DeltaTime);

private:
	// Floors x and y movement;
	float XMovement;
	float YMovement;
	float ShakeAmount;

	bool MoveOnScreen;
	bool Selected;

	// Floors target destination
	FVector Destination;
	FVector CurrentPosition;

public:
	bool MoveOffScreen;
	
	// Checks direction to move in
	bool MoveRight;
	bool MoveLeft;
	bool MoveUp;
	bool MoveDown;
};
