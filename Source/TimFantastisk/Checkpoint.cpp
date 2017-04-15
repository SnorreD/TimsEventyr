// Fill out your copyright notice in the Description page of Project Settings.

#include "TimFantastisk.h"
#include "Checkpoint.h"
#include "Tim.h"
#include "TimGameMode.h"
#include "MySaveGame.h"


// Sets default values
ACheckpoint::ACheckpoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootBox = CreateDefaultSubobject<UBoxComponent>(TEXT("MySphere"));
	RootComponent = RootBox;
	RootBox->bGenerateOverlapEvents = true;
	RootBox->OnComponentBeginOverlap.AddDynamic(this, &ACheckpoint::OnOverlap);

}

// Called when the game starts or when spawned
void ACheckpoint::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
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
		if (Cast<ATimGameMode>(GetWorld()->GetAuthGameMode())->SpawnPlace == NewCheck)
		{
			Destroy();
		}
		else
		{
			UMySaveGame* SavedGame = Cast<UMySaveGame>(UGameplayStatics::CreateSaveGameObject(UMySaveGame::StaticClass()));
			SavedGame->Map = Map;
			SavedGame->Level = NewCheck;

			UGameplayStatics::SaveGameToSlot(SavedGame, TEXT("LevelChange"), 0);

			Destroy();
		}	
	}
}

