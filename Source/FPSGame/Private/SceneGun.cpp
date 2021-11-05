// Fill out your copyright notice in the Description page of Project Settings.


#include "SceneGun.h"

#include <complex>

#include "MainPlayerController.h"
#include "../FPSGameCharacter.h"
#include "Kismet/GameplayStatics.h"

// #include "../FPSGameCharacter.h"

// Sets default values
ASceneGun::ASceneGun()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("GunSphereComp"));
	CollisionComp->InitSphereRadius(50.0);
	CollisionComp->SetCollisionProfileName("SceneGun");
	RootComponent = CollisionComp;
	
	MeshGun = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FP_Gun"));
	MeshGun->SetOnlyOwnerSee(false); // otherwise won't be visible in the multiplayer
	MeshGun->bCastDynamicShadow = false;
	MeshGun->CastShadow = false;
	// FP_Gun->SetupAttachment(Mesh1P, TEXT("GripPoint"));
	MeshGun->SetupAttachment(RootComponent);

	HighLight = CreateDefaultSubobject<USpotLightComponent>(TEXT("FP_GUN_LIGHT"));
	FRotator Rotator(-90,0,0);
	HighLight->AddRelativeRotation(Rotator);
	FVector LightPosition = HighLight->GetRelativeLocation();
	// LightPosition.Z += 100;
	HighLight->SetRelativeLocation(LightPosition);
	HighLight->SetLightColor(HighLightColor);
	HighLight->UpdateColorAndBrightness();
	HighLight->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ASceneGun::BeginPlay()
{
	Super::BeginPlay();
	CollisionComp->OnComponentHit.AddDynamic(this, &ASceneGun::OnTaken);
}

// Called every frame
void ASceneGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	RunningTime += DeltaTime;

	float ZOffset = SelfAmplitude * std::sin(SelfFrequency * RunningTime);
	FVector NewLocation = this->GetActorLocation();
	NewLocation.Z += ZOffset;
	this->SetActorLocation(NewLocation);

	FRotator Rotator(0,SelfRotationSpeed * RunningTime, 0);
	this->SetActorRotation(Rotator);
}

void ASceneGun::OnTaken(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	if(OtherActor != nullptr && OtherActor != this && OtherActor->Tags.Find("Player") != INDEX_NONE)
	{
		AMainPlayerController *MPC = dynamic_cast<AMainPlayerController*>(UGameplayStatics::GetPlayerController(this, 0));
		MPC->StartGame();
		AFPSGameCharacter *Player = dynamic_cast<AFPSGameCharacter*>(UGameplayStatics::GetPlayerCharacter(this, 0));
		Player->TakeWeapon();
		GEngine->AddOnScreenDebugMessage(0,2,FColor::Green, OtherActor->GetName());
		Destroy();
	}
	// && OtherActor->Tags.Find("Player") != INDEX_NONE
}
