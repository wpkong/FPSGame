// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TargetMovements/TargetMovementComponent.h"
#include "TargetLinearMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class FPSGAME_API UTargetLinearMovementComponent : public UTargetMovementComponent
{
	GENERATED_BODY()

public:
	FVector Opposite;
	FVector Origin;
	
public:
	virtual void BeginPlay() override;
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
