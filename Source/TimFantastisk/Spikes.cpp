// Fill out your copyright notice in the Description page of Project Settings.

#include "TimFantastisk.h"
#include "Spikes.h"
#include "Tim.h"


ASpikes::ASpikes()
{
	PrimaryActorTick.bCanEverTick = true;

	RootBox = CreateDefaultSubobject<UBoxComponent>(TEXT("MyBox"));
	RootComponent = RootBox;
	RootBox->bGenerateOverlapEvents = true;
	RootBox->OnComponentBeginOverlap.AddDynamic(this, &ASpikes::OnOverlap);
}

void ASpikes::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASpikes::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASpikes::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor *OtherActor,
	UPrimitiveComponent *OtherComponent, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult &SweepResult)
{
	//Hvis spilleren treffer piggene dør han.
	if (OtherActor->IsA(ATim::StaticClass()))
	{
		Cast<ATim>(OtherActor)->ImHit(3.f);
	}
}