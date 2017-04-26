// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Melee.generated.h"

UCLASS()
class TIMFANTASTISK_API AMelee : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMelee();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Tiden sverdet lever.
	UPROPERTY(EditAnywhere)
		float TimeBeforeDestroy = 0.25f;

	//Skaden sverdet gjør.
	UPROPERTY(EditAnywhere)
		float Damage = 1.f;

	float TimeLived{ 0 };

	UPROPERTY(EditAnywhere)
		UShapeComponent* RootCapsule = nullptr;

	UFUNCTION()
		void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor *OtherActor,
			UPrimitiveComponent *OtherComponent, int32 OtherBodyIndex,
			bool bFromSweep, const FHitResult &SweepResult);


	
	
};
