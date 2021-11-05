// Fill out your copyright notice in the Description page of Project Settings.


#include "TargetMovements/TargetLinearMovementComponent.h"
#include "cmath"

void UTargetLinearMovementComponent::BeginPlay()
{
	Super::BeginPlay();
	// Origin = GetOwner()->GetActorLocation();
}

void UTargetLinearMovementComponent::TickComponent(float DeltaTime, ELevelTick Tick,
                                                   FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, Tick, ThisTickFunction);

	float t = (std::cos(Alpha * RunningTime) + 1) / 2.0;
	FVector NewLocation = Origin * t + (1-t) * Opposite;
	GetOwner()->SetActorLocation(NewLocation);
}
