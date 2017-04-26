// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MySaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Actor.h"
#include "Checkpoint.generated.h"

UCLASS()
class TIMFANTASTISK_API ACheckpoint : public AActor
{
	GENERATED_BODY()
	
public:	

	ACheckpoint();

protected:

	virtual void BeginPlay() override;

public:	

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
		UShapeComponent* RootBox = nullptr;

	UFUNCTION()
		void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor *OtherActor,
			UPrimitiveComponent *OtherComponent, int32 OtherBodyIndex,
			bool bFromSweep, const FHitResult &SweepResult);

	//Den nye playerstart og kartet.
	UPROPERTY(EditAnywhere)
		FString NewCheck = "Level1_1";
	UPROPERTY(EditAnywhere)
		FName Map = "Skylevel";
	
};
