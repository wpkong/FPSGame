// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MainPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class FPSGAME_API AMainPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UUserWidget> BeforePlayHUDAsset;
	UUserWidget *BeforePlayHUD;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UUserWidget> HUDAsset;
	UUserWidget *HUD;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UUserWidget> StartPlayHUDAsset;
	UUserWidget *StartPlayHUD;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UUserWidget> FinishPlayHUDAsset;
	UUserWidget *FinishPlayHUD;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UUserWidget> TouchHUDAsset;
	UUserWidget *TouchHUD;

public:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void PrepareGame();

	UFUNCTION(BlueprintCallable)
	void StartGame();

	UFUNCTION(BlueprintCallable)
	void TerminationGame();
};
