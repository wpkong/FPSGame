// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSGame/Public/TargetMovements/TargetRoundMovementComponent.h"
#include "cmath"
#include "Kismet/KismetMathLibrary.h"


void UTargetRoundMovementComponent::BeginPlay()
{
	Super::BeginPlay();
	auto OwnerLocation = GetOwner()->GetActorLocation();
	R = FVector2D::Distance(FVector2D(OwnerLocation.X, OwnerLocation.Y), FVector2D(Origin.X, Origin.Y));

	Theta0.X = std::acos((OwnerLocation.X - Origin.X) / R);
	Theta0.Y = std::asin((OwnerLocation.Y - Origin.Y) / R);
}

void UTargetRoundMovementComponent::TickComponent(float DeltaTime, ELevelTick Tick,
                                                  FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, Tick, ThisTickFunction);
	
	FVector NewLocation(
		std::cos(Alpha * RunningTime + Theta0.X),
		std::sin(Alpha * RunningTime + Theta0.X),
		0
	);
	NewLocation = NewLocation * R + Origin;
	GetOwner()->SetActorLocation(NewLocation);
}
