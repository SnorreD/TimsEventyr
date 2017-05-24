// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "HjernetrimBryter.generated.h"

UCLASS()
class TIMFANTASTISK_API AHjernetrimBryter : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHjernetrimBryter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
		UShapeComponent* BryterBox = nullptr;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* BryterMesh;

	UPROPERTY(EditAnywhere)
		UShapeComponent* PuzzleBox = nullptr;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* Door;

	UFUNCTION()
		void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor *OtherActor,
			UPrimitiveComponent *OtherComponent, int32 OtherBodyIndex,
			bool bFromSweep, const FHitResult &SweepResult);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		bool PlayerActivate = false;

	//Movedistance 1: flytter døren, Movedistance 2: flytter knappen.
	UPROPERTY(EditAnywhere)
		float MoveDistance = 100.f;
	UPROPERTY(EditAnywhere)
		float MoveDistance2 = 20.f;

	UPROPERTY(EditAnywhere)
		float MoveTime = 10.f;

	//Fiender kan aktivere knappen, og døren/knappen vil gå opp igjen etter en stund før prossesen kan gjentas.
	UPROPERTY(EditAnywhere)
		bool AcceptMinions = false;

	float StartTime{ 0.f };
	
};
