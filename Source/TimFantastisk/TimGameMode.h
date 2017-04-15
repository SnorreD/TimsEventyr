// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameModeBase.h"
#include "TimGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TIMFANTASTISK_API ATimGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
		//UPROPERTY(EditAnywhere, Category = "Spawning")
		//TSubclassOf<class ATim> TimBlueprint;
public:
	ATimGameMode();

	void SaveGame();
	void LoadGame();

	FString SpawnPlace = "Level1_1";
	FName Map = "Prototype_Map";
	
};
