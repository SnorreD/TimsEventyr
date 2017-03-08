// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "AvstandFiende.generated.h"

UCLASS()
class TIMFANTASTISK_API AAvstandFiende : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAvstandFiende();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FVector CurrentVelocity;
	FVector NewDirection;

	UPROPERTY(EditAnywhere, Category = "Spawning")
		TSubclassOf<class ABullet> BulletBlueprint;

	float LastShot{ 0.f };
	float TimeBetweenShots{ 0.8f };
	
};
