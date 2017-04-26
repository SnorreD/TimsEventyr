// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Shield.generated.h"

UCLASS()
class TIMFANTASTISK_API AShield : public AActor
{
	GENERATED_BODY()
	
public:	

	AShield();

protected:

	virtual void BeginPlay() override;

public:	

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
		UShapeComponent* RootCapsule = nullptr;

	UPROPERTY(EditAnywhere)
		float CurrentCooldownTime = 0;

	UPROPERTY(EditAnywhere)
		float TotalCooldownTime = 0.5f;

	UFUNCTION()
		void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor *OtherActor,
			UPrimitiveComponent *OtherComponent, int32 OtherBodyIndex,
			bool bFromSweep, const FHitResult &SweepResult);

	float Health = 10.f;

	bool Cooldown = false;

};
