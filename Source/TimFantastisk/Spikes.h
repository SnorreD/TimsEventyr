// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Spikes.generated.h"

UCLASS()
class TIMFANTASTISK_API ASpikes : public AActor
{
	GENERATED_BODY()
	
public:	

	ASpikes();

protected:

	virtual void BeginPlay() override;

public:	

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
		UShapeComponent* RootBox = nullptr;

	UPROPERTY(EditAnywhere)
		bool Move = false;

	int MovementMode{ 1 };
	float MovementTime{ 1.f };
	float TimeSinceModeChange{ 0.f };

	UFUNCTION()
		void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor *OtherActor,
			UPrimitiveComponent *OtherComponent, int32 OtherBodyIndex,
			bool bFromSweep, const FHitResult &SweepResult);
	
};
