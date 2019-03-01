// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "StatModifier.generated.h"

UENUM(BlueprintType)
enum class EModifierCombinationMethod : uint8
{
	Stack		UMETA(DisplayName = "Stack"),
	Overwrite	UMETA(DisplayName = "Overwrite"),
	Discard		UMETA(DisplayName = "Discard")
};

UENUM(BlueprintType)
enum class EModifierType : uint8
{
	Speed		UMETA(DisplayName = "Speed"),
	Slowness	UMETA(DisplayName = "Slowness"),
	Stun		UMETA(DisplayName = "Stun"),
	ForcePush	UMETA(DisplayName = "ForcePush"),
	ForcePull	UMETA(DisplayName = "ForcePull"),
	Visibility	UMETA(DisplayName = "Visibility"),
	Reverse		UMETA(DisplayName = "Reverse")
};

USTRUCT(BlueprintType)
struct FStatModifier
{
	GENERATED_USTRUCT_BODY()

public:
	FStatModifier() :
		Amount(0.0f),
		Duration(0.0f),
		AmountCombinationMethod(EModifierCombinationMethod::Discard),
		DurationCombinationMethod(EModifierCombinationMethod::Discard)
	{}

	// Effect amount of the modifier - for exmaple the amount of speed to add, or strength of magnet.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Amount;

	// Time this modifier will last.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Duration;

	// How to handle combining the amount of this modifier.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EModifierCombinationMethod AmountCombinationMethod;

	// How to handle combining the duration of this modifier.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EModifierCombinationMethod DurationCombinationMethod;
};