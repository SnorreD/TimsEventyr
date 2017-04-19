// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Hjernetrim1.generated.h"

UCLASS()
class TIMFANTASTISK_API AHjernetrim1 : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHjernetrim1();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
		UShapeComponent* RootBox = nullptr;

	UFUNCTION()
		void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor *OtherActor,
			UPrimitiveComponent *OtherComponent, int32 OtherBodyIndex,
			bool bFromSweep, const FHitResult &SweepResult);

	UFUNCTION()
		void EndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		bool PlayerActivate = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Light, meta = (AllowPrivateAccess = "true"))
		int Light1 = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Light, meta = (AllowPrivateAccess = "true"))
		int Light2 = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Light, meta = (AllowPrivateAccess = "true"))
		int Light3 = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Light, meta = (AllowPrivateAccess = "true"))
		int Light4 = 1;
};
