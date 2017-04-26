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

	//Tips brukes sammen med 'HUD' og 'ShowTips' for � vise tips p� skjermen.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		FString Tips = "";

	//Hvor langt fiendene skal ned f�r de d�r.
	float KillZ = -900.f;
	
};
