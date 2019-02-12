// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "Engine/DataTable.h"
#include "StatModifier.h"

#include "Materials/Material.h"

#include "Powerup.generated.h"

USTRUCT(BlueprintType)
struct FPowerup : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	FPowerup() {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UMaterial * Icon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bTeleport;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bSpawnClones;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bSpawnDecoyTreasure;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FStatModifier SpeedModifier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FStatModifier SlownessModifier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FStatModifier StunModifier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FStatModifier ForcePullModifier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FStatModifier ForcePushModifier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FStatModifier VisibilityModifier;
};