// Fill out your copyright notice in the Description page of Project Settings.

#include "TimFantastisk.h"
#include "Shield.h"
#include "Bullet.h"
#include "Fiende.h"


// Sets default values
AShield::AShield()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("MyShield"));
	RootComponent = RootCapsule;
	RootCapsule->SetRelativeScale3D(FVector(0.5f, 1.5f, 1.5f));
	RootCapsule->bGenerateOverlapEvents = true;
	RootCapsule->OnComponentBeginOverlap.AddDynamic(this, &AShield::OnOverlap);

}

// Called when the game starts or when spawned
void AShield::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AShield::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Cooldown == true)
	{
		CurrentCooldownTime += DeltaTime;
		if (CurrentCooldownTime > TotalCooldownTime)
		{
			Cooldown = false;
		}
	}


}

void AShield::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor *OtherActor,
	UPrimitiveComponent *OtherComponent, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult &SweepResult)
{
	if (OtherActor->IsA(AFiende::StaticClass()))
	{
		if (Cooldown == false)
		{
			Health = Health - 1.f;

			Cooldown = true;
		}
											  //Destroy();
	}

	else if (OtherActor->IsA(ABullet::StaticClass()))
	{
		//OtherActor->SetActorRotation(FRotator(OtherActor->GetActorRotation().Pitch, OtherActor->GetActorRotation().Yaw * +180, OtherActor->GetActorRotation().Roll));
		Cast<ABullet>(OtherActor)->EnemyBullet = false;
		if (Cast<ABullet>(OtherActor)->Speed > 0)
			Cast<ABullet>(OtherActor)->Speed *= -1;

		Health = Health - 1.f;
	}

	if (Health <= 0.f)
	{
		DestroyShield();
	}

}

void AShield::DestroyShield()
{
	this->Destroy();
}
