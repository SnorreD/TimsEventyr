// Fill out your copyright notice in the Description page of Project Settings.

#include "TimFantastisk.h"
#include "Checkpoint.h"
#include "Tim.h"
#include "TimGameMode.h"
#include "MySaveGame.h"


ACheckpoint::ACheckpoint()
{
	PrimaryActorTick.bCanEverTick = true;

	RootBox = CreateDefaultSubobject<UBoxComponent>(TEXT("MySphere"));
	RootComponent = RootBox;
	RootBox->bGenerateOverlapEvents = true;
	RootBox->OnComponentBeginOverlap.AddDynamic(this, &ACheckpoint::OnOverlap);

}

void ACheckpoint::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACheckpoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACheckpoint::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor *OtherActor,
	UPrimitiveComponent *OtherComponent, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult &SweepResult)
{
	if (OtherActor->IsA(ATim::StaticClass()))
	{
		if (Cast<ATim>(OtherActor)->CurrentCheck != NewCheck || GetWorld()->GetMapName() != Map.ToString())
		{
			//Her lagres det informasjonen om hvem checkpoint man er i og hvilke kart når spilleren kommer borti.
			UMySaveGame* SaveGameInstance = Cast<UMySaveGame>(UGameplayStatics::CreateSaveGameObject(UMySaveGame::StaticClass()));
			SaveGameInstance->Map = Map;
			SaveGameInstance->Level = NewCheck;
			UGameplayStatics::SaveGameToSlot(SaveGameInstance, SaveGameInstance->SaveSlotName, SaveGameInstance->UserIndex);
		}

		Destroy();
	}
}

