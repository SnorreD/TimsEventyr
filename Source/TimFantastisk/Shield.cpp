// Fill out your copyright notice in the Description page of Project Settings.

#include "TimFantastisk.h"
#include "Shield.h"
#include "Bullet.h"
#include "Fiende.h"
#include "Tim.h"


AShield::AShield()
{
	PrimaryActorTick.bCanEverTick = true;

	RootCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("MyShield"));
	RootComponent = RootCapsule;
	RootCapsule->SetRelativeScale3D(FVector(0.5f, 1.5f, 1.5f));
	RootCapsule->bGenerateOverlapEvents = true;
	RootCapsule->OnComponentBeginOverlap.AddDynamic(this, &AShield::OnOverlap);

}

void AShield::BeginPlay()
{
	Super::BeginPlay();
	
}

void AShield::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Skyoldet skal ikke kunne ta evig fort med skade, så det er en nedteller mellom hver gang den kan ta skade.
	if (Cooldown == true)
	{
		CurrentCooldownTime += DeltaTime;
		if (CurrentCooldownTime > TotalCooldownTime)
		{
			Cooldown = false;
			CurrentCooldownTime = 0.f;
		}
	}


}

void AShield::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor *OtherActor,
	UPrimitiveComponent *OtherComponent, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult &SweepResult)
{
	//Hvis en fiende treffer skjoldet tar det skade, hvis en kule treffer det tar det skade og reflekterer kulen tilbake. Skjoldets liv vil også bli sendt til en variabel hos spilleren.
	if (OtherActor->IsA(AFiende::StaticClass()))
	{
		if (Cooldown == false)
		{
			Health = Health - 1.f;
			ACharacter* myCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
			Cast<ATim>(myCharacter)->ShieldHealth = Health;

			Cooldown = true;
		}
	}

	else if (OtherActor->IsA(ABullet::StaticClass()))
	{
		if (Cast<ABullet>(OtherActor)->EnemyBullet == true)
		{
			Cast<ABullet>(OtherActor)->EnemyBullet = false;
			if (Cast<ABullet>(OtherActor)->Speed > 0)
				Cast<ABullet>(OtherActor)->Speed *= -1;

			Health -= Cast<ABullet>(OtherActor)->Damage;
			ACharacter* myCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
			Cast<ATim>(myCharacter)->ShieldHealth = Health;
		}
	}

	if (Health <= 0.f)
	{
		Destroy();
	}

}

