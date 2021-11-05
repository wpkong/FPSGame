// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <random>
#include "SpawnVolume.generated.h"

UCLASS()
class FPSGAME_API ASpawnVolume : public AActor
{
	GENERATED_BODY()
	
	float LastGenTime = 0;

	float RunningTime = 0;

public:
	UPROPERTY()
	float GenTargetFreq = 2;
	
	bool *IsGamePlaying;

	struct 
	{
		std::mt19937 RandomEngine;
		std::uniform_real_distribution<double> RandomDistribution;
	} RandomGroup;
	
	
public:	
	// Sets default values for this actor's properties
	ASpawnVolume();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UBoxComponent *SpawningBox;

	UFUNCTION(BlueprintPure)
	FVector GetSpawnPoint() const;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<class ABaseTarget> PawnToSpawn;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	void GenTarget();
	
};
