// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/MovementComponent.h"
#include "TargetMovementComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FPSGAME_API UTargetMovementComponent : public UMovementComponent
{
	GENERATED_BODY()

public:
	float RunningTime = 0;

	// 速度控制
	UPROPERTY()
	float Alpha = 1;

public:	
	// Sets default values for this component's properties
	UTargetMovementComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	void LookAtMe(const FVector &NewPosition);
	
};
