// Fill out your copyright notice in the Description page of Project Settings.

#include "TimFantastisk.h"
#include "BossEncounter.h"
#include "Tim.h"
#include "Boss1.h"


// Sets default values
ABossEncounter::ABossEncounter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootBox = CreateDefaultSubobject<UBoxComponent>(TEXT("MyBox"));
	RootComponent = RootBox;
	RootBox->bGenerateOverlapEvents = true;
	RootBox->OnComponentBeginOverlap.AddDynamic(this, &ABossEncounter::OnOverlap);

}

// Called when the game starts or when spawned
void ABossEncounter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABossEncounter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABossEncounter::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor *OtherActor,
	UPrimitiveComponent *OtherComponent, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult &SweepResult)
{
	if (OtherActor->IsA(ABoss1::StaticClass()) && Boss != Cast<ABoss1>(OtherActor))
	{
		Boss = Cast<ABoss1>(OtherActor);
	}
		

	if (OtherActor->IsA(ATim::StaticClass()))
	{
		if (Boss->IsA(ABoss1::StaticClass()))
			Cast<ATim>(OtherActor)->Boss = Boss;
		//else
		//	Cast<ATim>(OtherActor)->Jump();
	}
}

