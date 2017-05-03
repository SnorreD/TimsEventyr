// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Boss1.generated.h"

UCLASS()
class TIMFANTASTISK_API ABoss1 : public AActor
{
	GENERATED_BODY()
	
public:	

	ABoss1();

protected:

	virtual void BeginPlay() override;

public:	

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
		UShapeComponent* RootCapsule = nullptr;

	//Avstanden før fienden kan angrepe.
	UPROPERTY(EditAnywhere, Category = "Shooting")
		float ShootDistance = 600.f;

	UPROPERTY(EditAnywhere, Category = "Shooting")
		TSubclassOf<class ABullet> BulletBlueprint;

	UPROPERTY(EditAnywhere, Category = "Shooting")
		TSubclassOf<class AFiende> FiendeBlueprint;

	UPROPERTY(EditAnywhere, Category = "Dead")
		TSubclassOf<class ALevelUp> PowerDrop;

	UPROPERTY(EditAnywhere, Category = "Dead")
		int PowerDropLevel = 0;
	UPROPERTY(EditAnywhere, Category = "Dead")
		FString PowerDropInfo = "";
	
	float LastShot{ 0.f };
	float TimeBetweenShots{ 0.2f };

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		float Health = 20.f;

	FVector NewDirection;

	//Variabler som har med skyte modus å gjøre.
	int Mode = 1;
	float ModeChangeTime = FMath::FRandRange(10.f, 20.f);
	float TimeSinceModeChange = 0.f;

	void ImHit(float Damage);

};
