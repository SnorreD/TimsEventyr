// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "EnemySpawn.generated.h"

UCLASS()
class TIMFANTASTISK_API AEnemySpawn : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemySpawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
		float TimeBetweenSpawned = 0.5f;

	UPROPERTY(EditAnywhere)
		int NumberOfEnemies = 10;

	float LastSpawn{ 0.f };
	int AmountSpawned{ 0 };
	bool PlayerClose{ false };

	FVector PlayerDistance;

	UPROPERTY(EditAnywhere, Category = "Spawning")
		bool CloseRangeEnemy = true; //Sann for nærkamp fiende og falsk for avstand fiende.

	UPROPERTY(EditAnywhere, Category = "Spawning")
		TSubclassOf<class AFiende> FiendeBlueprint;

	UPROPERTY(EditAnywhere, Category = "Spawning")
		TSubclassOf<class AAvstandFiende> AvstandFiendeBlueprint;

	UPROPERTY(EditAnywhere)
		UShapeComponent* RootSphere = nullptr;
	
};
