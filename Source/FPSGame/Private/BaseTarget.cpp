// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseTarget.h"
#include "NiagaraCore/Public/NiagaraCore.h"
#include "NiagaraFunctionLibrary.h"
#include "Blueprint/UserWidget.h"
#include "FPSGame/FPSGameProjectile.h"
#include "FPSGame/FPSGameCharacter.h"
#include "TargetMovements/TargetMovementComponent.h"

// Sets default values
ABaseTarget::ABaseTarget()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TargetPlate = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TargetPlate"));
	TargetPlate->SetupAttachment(RootComponent);

	TargetPlate->AddLocalRotation(FRotator(90,0,0));
}

// Called when the game starts or when spawned
void ABaseTarget::BeginPlay()
{
	Super::BeginPlay();
	TargetPlate->OnComponentHit.AddDynamic(this, &ABaseTarget::OnHit);
}


// Called to bind functionality to input
void ABaseTarget::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABaseTarget::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherActor->Tags.Find("Projectile") != INDEX_NONE))
	{
		
#ifdef DEBUG
		GEngine->AddOnScreenDebugMessage(0,200,FColor::Red, OtherActor->GetName());
		GEngine->AddOnScreenDebugMessage(1,200,FColor::Red, "Hit");
#endif
		AFPSGameProjectile *Projectile = dynamic_cast<AFPSGameProjectile *>(OtherActor);
		Award(Projectile->GetGunner());
		Explode();
		Destroy();
		// ShowScore();
	}
}

void ABaseTarget::Explode()
{
	FVector ExplosionPosition = TargetPlate->GetComponentLocation();
	
	if(NS_Explosion)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), NS_Explosion, ExplosionPosition);
	}
}

void ABaseTarget::Award(AFPSGameCharacter* Gunner)
{
	if(Gunner == nullptr) return;
	Gunner->Award(10);
	Gunner->AddScore(1);
	// GEngine->AddOnScreenDebugMessage(1,200,FColor::Red, "NBBBBBBB!");
}

// Called every frame
void ABaseTarget::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(MovementComponent)
	{
		MovementComponent->TickComponent(DeltaTime, ELevelTick::LEVELTICK_TimeOnly, NULL);
	}
}

