// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Fiende.generated.h"

UCLASS()
class TIMFANTASTISK_API AFiende : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AFiende();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FVector CurrentVelocity;
	FVector NewDirection;

	void ImHit(float Damage);

	UPROPERTY(EditAnywhere)
		UShapeComponent* RootCapsule = nullptr;

	float Health{ 2.f };
	bool Faen{ false };

	float HitBackTime{ 2.5f };

	UFUNCTION()
		void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor *OtherActor,
			UPrimitiveComponent *OtherComponent, int32 OtherBodyIndex,
			bool bFromSweep, const FHitResult &SweepResult);


};
