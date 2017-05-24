// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "LastBoss.generated.h"

UCLASS()
class TIMFANTASTISK_API ALastBoss : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALastBoss();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
		UShapeComponent* RootCapsule = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UShapeComponent* PlatformBox = nullptr;

	//En boks for høyre og venstre hånd som blir brukt ved nærangrep.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UShapeComponent* RightHandCapsule = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UShapeComponent* LeftHandCapsule = nullptr;

	//Avstanden før bossen kan angrepe.
	UPROPERTY(EditAnywhere, Category = "Shooting")
		float AttackDistance = 850.f;

	UPROPERTY(EditAnywhere, Category = "Shooting")
		TSubclassOf<class ABullet> BulletBlueprint;

	UPROPERTY(EditAnywhere, Category = "Movement")
		float speed = 500.f;

	float LastShot{ 0.f };
	float TimeBetweenShots{ 4.f };

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		float Health = 60.f;

	int BarrageCounter{ 0 };

	FVector NewDirection;

	//Variabler som har med skyte modus å gjøre.
	int Mode = 1;

	//////////////Brukes til animasjon/////////////////
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		bool Dead;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		bool Attack1;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		bool Attack2;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		bool Moving;
	//////////////////////////////////////////////////

	bool MeleeAttack{ false };

	bool Charge{ false };

	AActor* ChargeBullet;

	float BulletSize = 0.5f;

	void ImHit(float Damage);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		bool Finished;

	UFUNCTION()
		void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor *OtherActor,
			UPrimitiveComponent *OtherComponent, int32 OtherBodyIndex,
			bool bFromSweep, const FHitResult &SweepResult);

	UFUNCTION()
		void OnPlatform(UPrimitiveComponent* OverlappedComponent, AActor *OtherActor,
			UPrimitiveComponent *OtherComponent, int32 OtherBodyIndex,
			bool bFromSweep, const FHitResult &SweepResult);
	
};
