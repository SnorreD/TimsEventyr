// Fill out your copyright notice in the Description page of Project Settings.

#include "TimFantastisk.h"
#include "MySaveGame.h"




UMySaveGame::UMySaveGame()
{
	//Informasjon om lagresporet.
	SaveSlotName = TEXT("SaveSlot");
	UserIndex = 0;
}