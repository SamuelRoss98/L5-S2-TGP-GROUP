// Fill out your copyright notice in the Description page of Project Settings.

#include "PowerupProjectile.h"

#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
APowerupProjectile::APowerupProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DefaultRoot = CreateDefaultSubobject<USceneComponent>("DefaultRoot");
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	EffectTrigger = CreateDefaultSubobject<USphereComponent>("EffectTrigger");

	RootComponent = DefaultRoot;
	Mesh->SetupAttachment(DefaultRoot);
	EffectTrigger->SetupAttachment(Mesh);
}

// Called when the game starts or when spawned
void APowerupProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APowerupProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APowerupProjectile::SetPowerup(const FPowerup & Powerup)
{
	PowerupData = Powerup;
}

FPowerup APowerupProjectile::GetPowerup() const
{
	return PowerupData;
}

