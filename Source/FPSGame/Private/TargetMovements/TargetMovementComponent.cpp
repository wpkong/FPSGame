// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSGame/Public/TargetMovements/TargetMovementComponent.h"

#include "Kismet/KismetMathLibrary.h"

// Sets default values for this component's properties
UTargetMovementComponent::UTargetMovementComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTargetMovementComponent::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called every frame
void UTargetMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	RunningTime += DeltaTime;

	AActor *owner = GetOwner();
	if(owner)
	{
		auto Loc = owner->GetActorLocation();
		LookAtMe(Loc);
	}
}

void UTargetMovementComponent::LookAtMe(const FVector &NewPosition)
{
	auto Rotator = UKismetMathLibrary::FindLookAtRotation(NewPosition, GetWorld()->GetFirstPlayerController()->PlayerCameraManager->GetCameraLocation());
	FRotator AdjustRotator(90,0,0);
	GetOwner()->SetActorRotation(AdjustRotator + Rotator);
}

