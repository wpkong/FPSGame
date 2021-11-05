// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnVolume.h"
#include "BaseTarget.h"
#include "FPSGame/FPSGameCharacter.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "FPSGame/Public/TargetMovements/TargetRoundMovementComponent.h"
#include "FPSGame/Public/TargetMovements/TargetLinearMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include <random>

// Sets default values
ASpawnVolume::ASpawnVolume()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->SpawningBox = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawningBox"));
}

FVector ASpawnVolume::GetSpawnPoint() const
{
	const auto Extent = SpawningBox->GetScaledBoxExtent();
	const auto Origin = SpawningBox->GetComponentLocation();
	const auto Point = UKismetMathLibrary::RandomPointInBoundingBox(Origin, Extent);
	return Point;
}

// Called when the game starts or when spawned
void ASpawnVolume::BeginPlay()
{
	Super::BeginPlay();
	AFPSGameCharacter* Player = dynamic_cast<AFPSGameCharacter*>(UGameplayStatics::GetPlayerCharacter(this, 0));
	this->IsGamePlaying = &Player->IsGameRunning;
	RunningTime = 0;
	LastGenTime = 0;

	RandomGroup.RandomEngine = std::mt19937(std::random_device()());
	RandomGroup.RandomDistribution = std::uniform_real_distribution<double>(0, 1.0);
}

// Called every frame
void ASpawnVolume::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (IsGamePlaying && *IsGamePlaying)
	{
		RunningTime += DeltaTime;
		LastGenTime += DeltaTime;
		if (LastGenTime >= GenTargetFreq)
		{
			LastGenTime = 0;
			GenTarget();
		}
	}
}

void ASpawnVolume::GenTarget()
{
	const FRotator SpawnRotation(0, 0, 0);
	const FVector SpawnLocation = GetSpawnPoint();
	ABaseTarget* Target = GetWorld()->SpawnActor<ABaseTarget>(PawnToSpawn, SpawnLocation, SpawnRotation);

	UTargetMovementComponent* Mc = nullptr;

	double RandomValue = RandomGroup.RandomDistribution(RandomGroup.RandomEngine);

	double SpeedUpFactor = (std::log(RunningTime / 30.0 + 1) + 1) / 2;
	
	if (RandomValue < 0.2)
	{
		UTargetMovementComponent *MovementComponent = NewObject<UTargetMovementComponent>(Target);
		Mc = MovementComponent;
	}
	else if (RandomValue < 0.6)
	{
		UTargetRoundMovementComponent *MovementComponent = NewObject<UTargetRoundMovementComponent>(Target);
		MovementComponent->Origin = (SpawnLocation + GetSpawnPoint()) / 2;
		Mc = MovementComponent;
	}
	else
	{
		UTargetLinearMovementComponent *MovementComponent = NewObject<UTargetLinearMovementComponent>(Target);
		MovementComponent->Origin = SpawnLocation;
		MovementComponent->Opposite = GetSpawnPoint();
		Mc = MovementComponent;
	}
	if(Mc)
	{
		Mc->Alpha = SpeedUpFactor;
	}
	
	Target->SetTargetMovementComponent(Mc);
}
