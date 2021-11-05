// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "Components/SpotLightComponent.h"
#include "GameFramework/Actor.h"
#include "SceneGun.generated.h"

UCLASS()
class FPSGAME_API ASceneGun : public AActor
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
	USkeletalMeshComponent* MeshGun;

	UPROPERTY(EditAnywhere, Category=Mesh)
	USphereComponent* CollisionComp;

	UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
	USpotLightComponent *HighLight;

	UPROPERTY(EditAnywhere, Category=Movement)
	float SelfAmplitude = 1;

	UPROPERTY(EditAnywhere, Category=Movement)
	float SelfFrequency = 1;

	UPROPERTY(EditAnywhere, Category=Movement)
	float SelfRotationSpeed = 1;

	UPROPERTY(EditAnywhere, Category=Light)
	FLinearColor HighLightColor = FLinearColor::Green;

public:	
	// Sets default values for this actor's properties
	ASceneGun();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION()
	void OnTaken(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	
private:
	float RunningTime = 0;
};
