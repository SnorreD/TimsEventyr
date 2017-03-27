// Fill out your copyright notice in the Description page of Project Settings.

#include "TimFantastisk.h"
#include "Shield.h"
#include "Bullet.h"
#include "Fiende.h"
#include "Tim.h"


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

	//if (Tim)
	//{
	//	Tim->UpdateComponentTransforms();
	//	SetActorLocationAndRotation(Tim->GetActorLocation() + (Tim->GetActorForwardVector() * 100.f), Tim->GetActorRotation());
	//}

	/*if (Cooldown == true)
	{
		CurrentCooldownTime += DeltaTime;
		if (CurrentCooldownTime > TotalCooldownTime)
		{
			Cooldown = false;
		}
	}*/
	//FVector loc = Tim->GetActorLocation() + Tim->GetActorForwardVector() * 100.f;
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
		Cast<ABullet>(OtherActor)->Destroy();

		Health = Health - 1.f;
	}

	if (Health == 0.f)
	{
		this->Destroy();
	}

}
