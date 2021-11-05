// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TargetMovements/TargetMovementComponent.h"
#include "BaseTarget.generated.h"

class UNiagaraSystem;

UCLASS()
class FPSGAME_API ABaseTarget : public APawn
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category=Mesh)
	UStaticMeshComponent *TargetPlate;

	UPROPERTY(EditDefaultsOnly, Category=Effect)
	UNiagaraSystem *NS_Explosion;
	
	UPROPERTY()
	class UTargetMovementComponent *MovementComponent;

public:
	// Sets default values for this pawn's properties
	ABaseTarget();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION()
	void Explode();

	UFUNCTION()
	void Award(class AFPSGameCharacter* Gunner);

	void SetTargetMovementComponent(class UTargetMovementComponent *MC)
	{
		this->MovementComponent = MC;
		this->MovementComponent->RegisterComponent();
	}
};
