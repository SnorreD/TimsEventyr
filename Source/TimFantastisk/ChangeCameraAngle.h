// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "ChangeCameraAngle.generated.h"

UCLASS()
class TIMFANTASTISK_API AChangeCameraAngle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AChangeCameraAngle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
		UShapeComponent* RootCapsule = nullptr;

	UFUNCTION()
		void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor *OtherActor,
			UPrimitiveComponent *OtherComponent, int32 OtherBodyIndex,
			bool bFromSweep, const FHitResult &SweepResult);

	UPROPERTY(EditAnywhere, Category = "Camera")
		float ArmLenght = 1000.f;

	UPROPERTY(EditAnywhere, Category = "Camera")
		FRotator CameraRotation = FRotator(-60.f, 0.f, 0.f);
	
};
