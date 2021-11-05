// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayerController.h"

#include "FPSGame/FPSGameCharacter.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

void AMainPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	if (TouchHUDAsset)
	{
		TouchHUD = CreateWidget<UUserWidget>(this, TouchHUDAsset);
	}
	if (TouchHUD)
	{
		TouchHUD->AddToViewport();
	}
	
	
	PrepareGame();
}

void AMainPlayerController::StartGame()
{
	if (BeforePlayHUD)
	{
		BeforePlayHUD->RemoveFromViewport();
		BeforePlayHUD = nullptr;
	}
	
	if (StartPlayHUDAsset)
	{
		StartPlayHUD = CreateWidget<UUserWidget>(this, StartPlayHUDAsset);
	}
	if (StartPlayHUD)
	{
		StartPlayHUD->AddToViewport();
	}

	if (HUDAsset)
	{
		HUD = CreateWidget<UUserWidget>(this, HUDAsset);
	}
	if (HUD)
	{
		HUD->AddToViewport();
	}

	auto Character = UGameplayStatics::GetPlayerCharacter(this, 0);
	if (Character)
	{
		AFPSGameCharacter* Player = static_cast<AFPSGameCharacter*>(Character);
		Player->StartGame();
	}
}

void AMainPlayerController::TerminationGame()
{
	if (FinishPlayHUDAsset)
	{
		FinishPlayHUD = CreateWidget<UUserWidget>(this, FinishPlayHUDAsset);
	}
	if (FinishPlayHUD)
	{
		FinishPlayHUD->AddToViewport();
	}
}

void AMainPlayerController::PrepareGame()
{
	if (BeforePlayHUDAsset)
	{
		BeforePlayHUD = CreateWidget<UUserWidget>(this, BeforePlayHUDAsset);
	}
	if (BeforePlayHUD)
	{
		BeforePlayHUD->AddToViewport();
	}
}

