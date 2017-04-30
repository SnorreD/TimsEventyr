// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Bullet.generated.h"

UCLASS()
class TIMFANTASTISK_API ABullet : public AActor
{
	GENERATED_BODY()
	
public:	

	ABullet();

protected:

	virtual void BeginPlay() override;

public:	

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
		float Speed = 700.f;

	UPROPERTY(EditAnywhere)
		float TimeBeforeDestroy = 3.f;

	UPROPERTY(EditAnywhere)
		float Damage = 0.5f;

	float TimeLived{ 0.f };

	//Vi holder øye med om det er en fiende eller spilleren som har skutt kulen. Med denne variablen kommer vi unna vennlig skade.
	UPROPERTY(EditAnywhere)
		bool EnemyBullet = true;

	UPROPERTY(EditAnywhere)
		UShapeComponent* RootSphere = nullptr;

	UFUNCTION()
		void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor *OtherActor,
			UPrimitiveComponent *OtherComponent, int32 OtherBodyIndex,
			bool bFromSweep, const FHitResult &SweepResult);


	
};
