// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MySaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "Tim.generated.h"

UCLASS()
class TIMFANTASTISK_API ATim : public ACharacter
{
	GENERATED_BODY()

public:

	ATim();

protected:

	virtual void BeginPlay() override;


public:

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveX(float AxisValue);
	void MoveY(float AxisValue);
	void Jump();
	void AttackMelee();
	void AttackShoot();
	void AttackShootCharge();
	void ShieldOn();
	void ShieldOff();
	void ImHit(float Damage);

	FVector CurrentVelocity;
	int Mode{ 1 };

	UPROPERTY(EditAnywhere)
		int Speed = 400;

	//Kamera.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* TopDownCameraComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;

	//Markør.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UDecalComponent* CursorToWorld;

	//Objekter spilleren kan lage.
	UPROPERTY(EditAnywhere, Category = "Spawning")
		TSubclassOf<class ABullet> BulletBlueprint;
	UPROPERTY(EditAnywhere, Category = "Spawning")
		TSubclassOf<class AMelee> MeleeBlueprint;
	UPROPERTY(EditAnywhere, Category = "Spawning")
		TSubclassOf<class AShield> ShieldBlueprint;

	//Angrep variabler.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		bool Skytesperre = false;

	//Sann for Avstand, falsk for nærangrep.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		int RangeMelee = 0;

	UPROPERTY(EditAnywhere)
		float AngrepMellomrom = 0.5f;

	UPROPERTY(EditAnywhere)
		FString CurrentCheck;

	float TidSidenAngrep;

	//Skjold variabler.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		float ShieldHealth = 5.f;

	float ShieldTimer{ 10.f };
	float ShieldDestroyed = 0.f;
	bool ShieldDestruction = false;
	AActor *Shield;
	AActor *ChargeBullet;
	bool Charge{ false };
	bool ShieldOut{ false };

	AActor *Rope = nullptr;
	bool Climbing{ false };

	bool DamageTaken{ false };
	float DamageInv{ 0.3f };
	float TimeSinceDam = 0.f;

	bool DoubleJump{ false };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
		int Level;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		int Health = 3;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		bool Ded = false;

	//Puzzle variablen brukes for å peke på en gåte spilleren er på.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		AActor* Puzzle;

	//Boss variablen brukes for å peke på en boss spilleren er på.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		AActor* Boss;
};
