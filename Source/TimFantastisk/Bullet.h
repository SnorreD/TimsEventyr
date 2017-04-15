// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Bullet.generated.h"

UCLASS()
class TIMFANTASTISK_API ABullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABullet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
		float Speed = 700.f;

	UPROPERTY(EditAnywhere)
		float TimeBeforeDestroy = 500.f;

	UPROPERTY(EditAnywhere)
		float Damage = 0.5f;

	float TimeLived{ 0.f };

	UPROPERTY(EditAnywhere)
		bool EnemyBullet = true;

	UPROPERTY(EditAnywhere)
		UShapeComponent* RootSphere = nullptr;

	UFUNCTION()
		void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor *OtherActor,
			UPrimitiveComponent *OtherComponent, int32 OtherBodyIndex,
			bool bFromSweep, const FHitResult &SweepResult);


	
};
