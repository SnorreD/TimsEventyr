// Fill out your copyright notice in the Description page of Project Settings.

#include "TimFantastisk.h"
#include "TimGameMode.h"
#include "Tim.h"
#include "MySaveGame.h"


ATimGameMode::ATimGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/TimBlueprint"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void ATimGameMode::SaveGame()
{
	UMySaveGame* SavedGame = Cast<UMySaveGame>(UGameplayStatics::CreateSaveGameObject(UMySaveGame::StaticClass()));
	SavedGame->Map = Map;
	SavedGame->Level = SpawnPlace;

	UGameplayStatics::SaveGameToSlot(SavedGame, TEXT("LevelChange"), 0);
}

void ATimGameMode::LoadGame()
{
	UMySaveGame* SavedGame = Cast<UMySaveGame>(UGameplayStatics::CreateSaveGameObject(UMySaveGame::StaticClass()));

	SavedGame = Cast<UMySaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("LevelChange"), 0));

	if (SavedGame)
	{
		this->Map = SavedGame->Map;
		//UE_LOG(LogTemp, Warning, TEXT("Loaded Map: %d"), Map)
		this->SpawnPlace = SavedGame->Level;
		//UE_LOG(LogTemp, Warning, TEXT("Loaded Checkpoint: %d"), SpawnPlace)	
	}
	else
	{
		//UE_LOG(LogTemp, Error, TEXT("Loading failed"))
	}
}

