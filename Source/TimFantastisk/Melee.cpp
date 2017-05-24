// Fill out your copyright notice in the Description page of Project Settings.

#include "TimFantastisk.h"
#include "Melee.h"
#include "Fiende.h"
#include "AvstandFiende.h"
#include "Bullet.h"
#include "Boss1.h"
#include "Hjernetrim2Fiende.h"
#include "LastBoss.h"


// Sets default values
AMelee::AMelee()
{
	PrimaryActorTick.bCanEverTick = true;

	RootCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("MySword"));
	RootComponent = RootCapsule;
	RootCapsule->SetRelativeScale3D(FVector(1.5f, 1.5f, 1.5f));
	RootCapsule->bGenerateOverlapEvents = true;
	RootCapsule->OnComponentBeginOverlap.AddDynamic(this, &AMelee::OnOverlap);

}

void AMelee::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMelee::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Sverdet liver bare en kort stund før den blir ødelagt.
	TimeLived += DeltaTime;
	if (TimeLived > TimeBeforeDestroy)
	{
		this->Destroy();
	}

}

void AMelee::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor *OtherActor,
	UPrimitiveComponent *OtherComponent, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult &SweepResult)
{
	if (!HaveHit)
	{
		//Hvis sverdet treffer en fiende tar fienden skade.
		if (OtherActor->IsA(AFiende::StaticClass()))
		{
			Cast<AFiende>(OtherActor)->ImHit(Damage);
			HaveHit = true;
		}
		else if (OtherActor->IsA(AAvstandFiende::StaticClass()))
		{
			Cast<AAvstandFiende>(OtherActor)->ImHit(Damage);
			HaveHit = true;
		}
		else if (OtherActor->IsA(ABoss1::StaticClass()))
		{
			Cast<ABoss1>(OtherActor)->ImHit(Damage);
			HaveHit = true;
		}
		else if (OtherActor->IsA(AHjernetrim2Fiende::StaticClass()))
		{
			Cast<AHjernetrim2Fiende>(OtherActor)->ImHit(Damage);
			HaveHit = true;
		}
		else if (OtherActor->IsA(ALastBoss::StaticClass()))
		{
			Cast<ALastBoss>(OtherActor)->ImHit(Damage);
			HaveHit = true;
		}
	}
	//Hvis sverdet treffer en kule ødeleges kulen (så lenge kulen ikke er sterk).
	if (OtherActor->IsA(ABullet::StaticClass()))
	{
		if (Cast<ABullet>(OtherActor)->StrongBullet == false)
			Cast<ABullet>(OtherActor)->Destroy();
	}
}

