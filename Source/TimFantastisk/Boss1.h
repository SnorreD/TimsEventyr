// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Boss1.generated.h"

UCLASS()
class TIMFANTASTISK_API ABoss1 : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABoss1();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
		UShapeComponent* RootCapsule = nullptr;

	UPROPERTY(EditAnywhere, Category = "Shooting")
		float ShootDistance = 600.f;

	UPROPERTY(EditAnywhere, Category = "Shooting")
		TSubclassOf<class ABullet> BulletBlueprint;
	
	float LastShot{ 0.f };
	float TimeBetweenShots{ 0.1f };

	float Health{ 10.f };
	FVector NewDirection;
	int Mode = 1;
	float ModeChangeTime = FMath::FRandRange(10.f, 20.f);
	float TimeSinceModeChange = 0.f;

	void ImHit(float Damage);

};
