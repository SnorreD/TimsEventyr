// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "EnemySpawn.generated.h"

UCLASS()
class TIMFANTASTISK_API AEnemySpawn : public AActor
{
	GENERATED_BODY()
	
public:	

	AEnemySpawn();

protected:

	virtual void BeginPlay() override;

public:	

	virtual void Tick(float DeltaTime) override;

	//Mellomrommet mellom hver fiende.
	UPROPERTY(EditAnywhere)
		float TimeBetweenSpawned = 0.5f;

	//Antall fiender som skal bli skapt.
	UPROPERTY(EditAnywhere)
		int NumberOfEnemies = 10;

	//Tellere.
	float LastSpawn{ 0.f };
	int AmountSpawned{ 0 };


	bool PlayerClose{ false };

	FVector PlayerDistance;

	UPROPERTY(EditAnywhere, Category = "Spawning")
		bool CloseRangeEnemy = true; //Sann for nærkamp fiende og falsk for avstand fiende.

	UPROPERTY(EditAnywhere, Category = "Spawning")
		TSubclassOf<class AFiende> FiendeBlueprint2;

	UPROPERTY(EditAnywhere, Category = "Spawning")
		TSubclassOf<class AAvstandFiende> AvstandFiendeBlueprint;

	UPROPERTY(EditAnywhere)
		UShapeComponent* RootSphere = nullptr;

	//Avstanden fra spilleren før fienden kan å gyte.
	UPROPERTY(EditAnywhere, Category = "Spawning")
		float SpawnDistance = 600.f;
	
};
