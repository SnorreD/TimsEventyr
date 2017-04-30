// Fill out your copyright notice in the Description page of Project Settings.

#include "TimFantastisk.h"
#include "Bullet.h"
#include "Fiende.h"
#include "Tim.h"
#include "AvstandFiende.h"
#include "Boss1.h"


ABullet::ABullet()
{
	PrimaryActorTick.bCanEverTick = true;

	RootSphere = CreateDefaultSubobject<USphereComponent>(TEXT("MySphere"));
	RootComponent = RootSphere;
	RootSphere->bGenerateOverlapEvents = true;
	RootSphere->OnComponentBeginOverlap.AddDynamic(this, &ABullet::OnOverlap);
}

void ABullet::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Flytter kulen baser på farten den har.
	FVector NewLocation = GetActorLocation();
	NewLocation += GetActorForwardVector() * Speed * DeltaTime;
	SetActorLocation(NewLocation);

	//Etter en viss mengde tid blir kulen ødelagt.
	TimeLived += DeltaTime;
	if (TimeLived > TimeBeforeDestroy)
	{
		this->Destroy();
	}
	

}

void ABullet::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor *OtherActor,
	UPrimitiveComponent *OtherComponent, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult &SweepResult)
{
	//Kulen tar skade på det den traffer.

	if (OtherActor->IsA(AFiende::StaticClass()) && EnemyBullet == false)
	{
		Cast<AFiende>(OtherActor)->ImHit(Damage);
		Destroy();
	}

	else if (OtherActor->IsA(ATim::StaticClass()) && EnemyBullet == true)
	{
		Cast<ATim>(OtherActor)->ImHit(Damage * 2);
		Destroy();
	}

	else if (OtherActor->IsA(AAvstandFiende::StaticClass()) && EnemyBullet == false)
	{
		Cast<AAvstandFiende>(OtherActor)->ImHit(Damage);
		Destroy();
	}
	else if (OtherActor->IsA(ABoss1::StaticClass()) && EnemyBullet == false)
	{
		Cast<ABoss1>(OtherActor)->ImHit(Damage);
		Destroy();
	}
	else if (OtherComponent->ComponentHasTag("Block"))
		Destroy();
}

