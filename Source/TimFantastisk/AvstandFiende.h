// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "AvstandFiende.generated.h"

UCLASS()
class TIMFANTASTISK_API AAvstandFiende : public AActor
{
	GENERATED_BODY()
	
public:	

	AAvstandFiende();

protected:

	virtual void BeginPlay() override;

public:	

	virtual void Tick(float DeltaTime) override;

	FVector CurrentVelocity;
	FVector NewDirection;

	UPROPERTY(EditAnywhere, Category = "Spawning")
		TSubclassOf<class ABullet> BulletBlueprint;

	UPROPERTY(EditAnywhere)
		UShapeComponent* RootCapsule = nullptr;

	//Avstanden fra spilleren før fienden kan begynne å skyte.
	UPROPERTY(EditAnywhere, Category = "Movement")
		float ShootDistance = 600.f;

	//Avstanden fra spilleren før fienden kan begynne å følge etter spilleren.
	UPROPERTY(EditAnywhere, Category = "Movement")
		float MoveDistance = 800.f;

	float LastShot{ 0.f };
	float TimeBetweenShots{ 0.8f };

	UPROPERTY(EditAnywhere)
		float Health = 1.f;
	
	void ImHit(float Damage);
};
