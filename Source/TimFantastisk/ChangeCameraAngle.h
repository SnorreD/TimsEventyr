// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "ChangeCameraAngle.generated.h"

UCLASS()
class TIMFANTASTISK_API AChangeCameraAngle : public AActor
{
	GENERATED_BODY()
	
public:	

	AChangeCameraAngle();

protected:

	virtual void BeginPlay() override;

public:	

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
		UShapeComponent* RootCapsule = nullptr;

	UFUNCTION()
		void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor *OtherActor,
			UPrimitiveComponent *OtherComponent, int32 OtherBodyIndex,
			bool bFromSweep, const FHitResult &SweepResult);

	UFUNCTION()
		void EndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY(EditAnywhere, Category = "Camera")
		bool WhileIn = false;

	UPROPERTY(EditAnywhere, Category = "Camera")
		float ArmLenght_In = 1000.f;

	UPROPERTY(EditAnywhere, Category = "Camera")
		FRotator CameraRotation_In = FRotator(-60.f, 0.f, 0.f);

	UPROPERTY(EditAnywhere, Category = "Camera")
		float ArmLenght_Out = 800.f;

	UPROPERTY(EditAnywhere, Category = "Camera")
		FRotator CameraRotation_Out = FRotator(-60.f, 0.f, 0.f);
	
};
