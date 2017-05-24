// Fill out your copyright notice in the Description page of Project Settings.

#include "TimFantastisk.h"
#include "TimGameMode.h"
#include "Tim.h"
#include "MySaveGame.h"


ATimGameMode::ATimGameMode()
{
	//Lager spilleren når spillet starter.
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/Karakterer/TimBlueprint"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

