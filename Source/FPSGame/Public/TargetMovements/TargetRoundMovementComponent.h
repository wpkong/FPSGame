// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TargetMovements/TargetMovementComponent.h"
#include "TargetRoundMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class FPSGAME_API UTargetRoundMovementComponent : public UTargetMovementComponent
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	
	FVector Origin;

	float R;

	FVector2D Theta0;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
