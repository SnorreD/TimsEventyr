// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "FiendeMovementBox.generated.h"

//Et veldig scriptet forsøk på AI


UCLASS()
class TIMFANTASTISK_API AFiendeMovementBox : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFiendeMovementBox();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	int EnemysCount{ 1 };

	//Hoppe: Velg 1 for å bruke på første fienden, 2 for andre, osv. Velg 0 for ingen eller 5 for alle 
	UPROPERTY(EditAnywhere, Category = "Movement")
		int Jump = 0;

	//Velg høyden på hoppet. 
	UPROPERTY(EditAnywhere, Category = "Movement")
		int JumpHeight = 0;
	
	//Snu 180grader: Velg 1 for å bruke på første fienden, 2 for andre, osv. Velg 0 for ingen eller 5 for alle.
	UPROPERTY(EditAnywhere, Category = "Movement")
		int Move180 = 0;

	//Snu 90 grader til høyre: Velg 1 for å bruke på første fienden, 2 for andre, osv. Velg 0 for ingen eller 5 for alle.
	UPROPERTY(EditAnywhere, Category = "Movement")
		int Move90right = 0;

	//Snu 90 grader til venstre: Velg 1 for å bruke på første fienden, 2 for andre, osv. Velg 0 for ingen eller 5 for alle.
	UPROPERTY(EditAnywhere, Category = "Movement")
		int Move90left = 0;

	//Sett rotasjon til dette objektet: Velg 1 for å bruke på første fienden, 2 for andre, osv. Velg 0 for ingen eller 5 for alle.
	UPROPERTY(EditAnywhere, Category = "Movement")
		int MoveToThis = 0;

	//Teleporter til lokalasjon: Velg 1 for å bruke på første fienden, 2 for andre, osv. Velg 0 for ingen eller 5 for alle.
	UPROPERTY(EditAnywhere, Category = "Actions")
		int teleport = 0;

	//Teleporteringplass.
	UPROPERTY(EditAnywhere, Category = "Actions")
		FVector tele;

	//Gå til kamp modus: Velg 1 for å bruke på første fienden, 2 for andre, osv. Velg 0 for ingen eller 5 for alle.
	UPROPERTY(EditAnywhere, Category = "Actions")
		int FightAfter = 0;

	//Ødelegg komponenten etter et visst antall fiender har passert den.
	UPROPERTY(EditAnywhere, Category = "Actions")
		int DestroyAfter = 4;
	
	UPROPERTY(EditAnywhere)
		UShapeComponent* RootBox = nullptr;

	UFUNCTION()
		void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor *OtherActor,
			UPrimitiveComponent *OtherComponent, int32 OtherBodyIndex,
			bool bFromSweep, const FHitResult &SweepResult);

	void StartJump(AActor *OtherActor);
};
