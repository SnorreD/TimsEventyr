// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Rope.generated.h"

UCLASS()
class TIMFANTASTISK_API ARope : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARope();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
		UShapeComponent* RootBox = nullptr;

	UPROPERTY(EditAnywhere)
		UShapeComponent* LiftBox = nullptr;


	UFUNCTION()
		void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor *OtherActor,
			UPrimitiveComponent *OtherComponent, int32 OtherBodyIndex,
			bool bFromSweep, const FHitResult &SweepResult);

	float Velocity{ 0.f };


	UPROPERTY(EditAnywhere, Category = "Movement")
		float MaxHeight;

	UPROPERTY(EditAnywhere, Category = "Movement")
		float MinHeight;
	
};
