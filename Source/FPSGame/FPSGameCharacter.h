// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include <algorithm>

#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Character.h"
#include "FPSGameCharacter.generated.h"

class UInputComponent;
class USkeletalMeshComponent;
class USceneComponent;
class UCameraComponent;
class UMotionControllerComponent;
class UAnimMontage;
class USoundBase;

UCLASS(config=Game)
class AFPSGameCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
	float CurrentHealth = 100;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
	float MaxHealth = 100;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
	float CountSeconds = 0;

	UPROPERTY(VisibleDefaultsOnly)
	int Score = 0;

	bool IsGameRunning = false;

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
	USkeletalMeshComponent* Mesh1P;

	/** Gun mesh: 1st person view (seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	USkeletalMeshComponent* FP_Gun;

	/** Location on gun mesh where projectiles should spawn. */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	USceneComponent* FP_MuzzleLocation;

	/** Gun mesh: VR view (attached to the VR controller directly, no arm, just the actual gun) */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	USkeletalMeshComponent* VR_Gun;

	/** Location on VR gun mesh where projectiles should spawn. */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	USceneComponent* VR_MuzzleLocation;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

	/** Motion controller (right hand) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UMotionControllerComponent* R_MotionController;

	/** Motion controller (left hand) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UMotionControllerComponent* L_MotionController;

	UPROPERTY(EditAnywhere, Category=Camera)
	float CameraDefaultFOV = 90.0f;

	UPROPERTY(EditAnywhere, Category=Camera)
	float CameraZoomFOV = 70.0f;

public:
	AFPSGameCharacter();

protected:
	virtual void BeginPlay();

public:
	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	/** Gun muzzle's offset from the characters location */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	FVector GunOffset;

	/** Projectile class to spawn */
	UPROPERTY(EditDefaultsOnly, Category=Projectile)
	TSubclassOf<class AFPSGameProjectile> ProjectileClass;

	/** Sound to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	USoundBase* FireSound;

	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	UAnimMontage* FireAnimation;

	/** Whether to use motion controller location for aiming. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	uint8 bUsingMotionControllers : 1;

	UPROPERTY()
	class UTimelineComponent* ZoomTimeline;

	UPROPERTY()
	UCurveFloat* FloatCurve;

	UPROPERTY()
	TEnumAsByte<ETimelineDirection::Type> TimelineDirection;

public:
	/** Fires a projectile. */
	UFUNCTION(BlueprintCallable)
	void OnFire();

	/** Resets HMD orientation and position in VR. */
	void OnResetVR();

	/** Handles moving forward/backward */
	void MoveForward(float Val);

	/** Handles stafing movement, left and right */
	void MoveRight(float Val);

	/**
	 * Called via input to turn at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	UFUNCTION(BlueprintCallable)
	void ZoomIn();

	UFUNCTION(BlueprintCallable)
	void ZoomOut();

	UFUNCTION(BlueprintCallable)
	float GetHealthPercent() const { return CurrentHealth * 1.0 / MaxHealth; }
	
	UFUNCTION(BlueprintCallable)
	float GetRunningSeconds() const { return CountSeconds; }

	UFUNCTION()
	void TimelineCallback(float Val);

	UFUNCTION()
	void TimelineFinishedCallback();

	struct TouchData
	{
		TouchData()
		{
			bIsPressed = false;
			Location = FVector::ZeroVector;
		}

		bool bIsPressed;
		ETouchIndex::Type FingerIndex;
		FVector Location;
		bool bMoved;
	};

	void BeginTouch(const ETouchIndex::Type FingerIndex, const FVector Location);
	void EndTouch(const ETouchIndex::Type FingerIndex, const FVector Location);
	void TouchUpdate(const ETouchIndex::Type FingerIndex, const FVector Location);
	TouchData TouchItem;

	/* Whether taken weapons */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GamePlay)
	bool bTakenWeapon = false;

public:
	UFUNCTION(BlueprintCallable, Category=GamePlay)
	void TakeWeapon();

	UFUNCTION(BlueprintCallable, Category=GamePlay)
	void Disarm();

	UFUNCTION()
	void Award(float Value);

	UFUNCTION()
	void Damage(float Value);

	UFUNCTION()
	void TickPunishment(float DeltaTime);

	UFUNCTION()
	void StartGame();

	UFUNCTION(BlueprintCallable)
	int GetScore() const { return Score; }

	UFUNCTION(BlueprintCallable)
	void AddScore(int Value)
	{
		if(IsGameRunning)
			Score += Value;
	}

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface

	/* 
	 * Configures input for touchscreen devices if there is a valid touch interface for doing so 
	 *
	 * @param	InputComponent	The input component pointer to bind controls to
	 * @returns true if touch controls were enabled.
	 */
	bool EnableTouchscreenMovement(UInputComponent* InputComponent);

public:
	/** Returns Mesh1P subobject **/
	USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	/** Returns FirstPersonCameraComponent subobject **/
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }


public:
	virtual void Tick(float DeltaSeconds) override;
};
