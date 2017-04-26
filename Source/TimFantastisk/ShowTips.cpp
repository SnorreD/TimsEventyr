// Fill out your copyright notice in the Description page of Project Settings.

#include "TimFantastisk.h"
#include "ShowTips.h"
#include "Tim.h"
#include "TimGameMode.h"


AShowTips::AShowTips()
{
	PrimaryActorTick.bCanEverTick = true;

	RootBox = CreateDefaultSubobject<UBoxComponent>(TEXT("MyBox"));
	RootComponent = RootBox;
	RootBox->bGenerateOverlapEvents = true;
	RootBox->OnComponentBeginOverlap.AddDynamic(this, &AShowTips::OnOverlap);
	RootBox->OnComponentEndOverlap.AddDynamic(this, &AShowTips::EndOverlap);

}

void AShowTips::BeginPlay()
{
	Super::BeginPlay();
	
}

void AShowTips::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//Hvis spilleren treffer tips kommer det tekst opp på skjermen med tips.
void AShowTips::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor *OtherActor,
	UPrimitiveComponent *OtherComponent, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult &SweepResult)
{
	if (OtherActor->IsA(ATim::StaticClass()))
	{
		auto CurrentGameMode = Cast<ATimGameMode>(GetWorld()->GetAuthGameMode());
		CurrentGameMode->Tips = tips;
	}
}

void AShowTips::EndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->IsA(ATim::StaticClass()))
	{
		auto CurrentGameMode = Cast<ATimGameMode>(GetWorld()->GetAuthGameMode());
		CurrentGameMode->Tips = "";
	}
}

