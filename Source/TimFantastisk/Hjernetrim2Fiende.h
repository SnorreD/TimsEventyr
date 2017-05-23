// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Hjernetrim2Fiende.generated.h"

UCLASS()
class TIMFANTASTISK_API AHjernetrim2Fiende : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHjernetrim2Fiende();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "Movement")
		float CurrentSpeed = 800.f;

	bool StartTurn{ false };
	float TurnDegree;
	void Turn(float DeltaTime);

	bool Attack{ false };

	UPROPERTY(EditAnywhere, Category = "Attack")
		int AttackMode;

	float TurnTime{ 1.f };
	float TimeSinceTurn{ 0.f };
	float Timer{ 0.f };

	UPROPERTY(EditAnywhere, Category = "Attack")
		TSubclassOf<class ABullet> BulletBlueprint;
	UPROPERTY(EditAnywhere, Category = "Attack")
		TSubclassOf<class AFiende> FiendeBlueprint;

	UPROPERTY(EditAnywhere)
		UShapeComponent* RootCapsule = nullptr;

	//Avstanden fra spilleren før fienden kan begynne å skyte.
	UPROPERTY(EditAnywhere, Category = "Attack")
		float ShootDistance = 900.f;

	float LastShot{ 0.f };
	float TimeBetweenShots;
	int BarrageCounter{ 0 };

	UPROPERTY(EditAnywhere)
		float Health = 10.f;

	void ImHit(float Damage);
	void StartAttacking(float DeltaTime);
	void SetAttackMode(int Mode);

	bool FiendeTag = false;
	
};
