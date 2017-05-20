// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Hjernetrim2.generated.h"

UCLASS()
class TIMFANTASTISK_API AHjernetrim2 : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHjernetrim2();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void OverlapContainer(int tall);

	//Komponenter
	UPROPERTY(EditAnywhere)
		UShapeComponent *Wait = nullptr;

	UPROPERTY(EditAnywhere)
		UShapeComponent* Entrance = nullptr;

	UPROPERTY(EditAnywhere)
		UShapeComponent* Key = nullptr;

	UPROPERTY(EditAnywhere)
		USceneComponent* Alter = nullptr;

	UPROPERTY(EditAnywhere)
		UShapeComponent* BlueContainer = nullptr;
	UPROPERTY(EditAnywhere)
		UShapeComponent* GreenContainer = nullptr;
	UPROPERTY(EditAnywhere)
		UShapeComponent* PinkContainer = nullptr;
	UPROPERTY(EditAnywhere)
		UShapeComponent* RedContainer = nullptr;
	UPROPERTY(EditAnywhere)
		UShapeComponent* BlueCrystal = nullptr;
	UPROPERTY(EditAnywhere)
		USceneComponent* BlueCrystalMesh;
	UPROPERTY(EditAnywhere)
		UShapeComponent* GreenCrystal = nullptr;
	UPROPERTY(EditAnywhere)
		USceneComponent* GreenCrystalMesh;
	UPROPERTY(EditAnywhere)
		UShapeComponent* PinkCrystal = nullptr;
	UPROPERTY(EditAnywhere)
		USceneComponent* PinkCrystalMesh;
	UPROPERTY(EditAnywhere)
		UShapeComponent* RedCrystal = nullptr;
	UPROPERTY(EditAnywhere)
		USceneComponent* RedCrystalMesh;

	UPROPERTY(EditAnywhere)
		USceneComponent* Spawn1;
	UPROPERTY(EditAnywhere)
		USceneComponent* Spawn2;
	UPROPERTY(EditAnywhere)
		USceneComponent* Spawn3;
	UPROPERTY(EditAnywhere)
		USceneComponent* Spawn4;

	UPROPERTY(EditAnywhere, Category = "Spawning")
		TSubclassOf<class AHjernetrim2Fiende> FiendeBlueprint;

	UPROPERTY(EditAnywhere, Category = "Spawning")
		float WaitTime = 18.f;

	//Kollisjon
	UFUNCTION()
		void OnOverlapBlueCo(UPrimitiveComponent* OverlappedComponent, AActor *OtherActor,
			UPrimitiveComponent *OtherComponent, int32 OtherBodyIndex,
			bool bFromSweep, const FHitResult &SweepResult);
	UFUNCTION()
		void OnOverlapGreenCo(UPrimitiveComponent* OverlappedComponent, AActor *OtherActor,
			UPrimitiveComponent *OtherComponent, int32 OtherBodyIndex,
			bool bFromSweep, const FHitResult &SweepResult);
	UFUNCTION()
		void OnOverlapPinkCo(UPrimitiveComponent* OverlappedComponent, AActor *OtherActor,
			UPrimitiveComponent *OtherComponent, int32 OtherBodyIndex,
			bool bFromSweep, const FHitResult &SweepResult);
	UFUNCTION()
		void OnOverlapRedCo(UPrimitiveComponent* OverlappedComponent, AActor *OtherActor,
			UPrimitiveComponent *OtherComponent, int32 OtherBodyIndex,
			bool bFromSweep, const FHitResult &SweepResult);

	UFUNCTION()
		void OnOverlapBlueCr(UPrimitiveComponent* OverlappedComponent, AActor *OtherActor,
			UPrimitiveComponent *OtherComponent, int32 OtherBodyIndex,
			bool bFromSweep, const FHitResult &SweepResult);
	UFUNCTION()
		void OnOverlapGreenCr(UPrimitiveComponent* OverlappedComponent, AActor *OtherActor,
			UPrimitiveComponent *OtherComponent, int32 OtherBodyIndex,
			bool bFromSweep, const FHitResult &SweepResult);
	UFUNCTION()
		void OnOverlapPinkCr(UPrimitiveComponent* OverlappedComponent, AActor *OtherActor,
			UPrimitiveComponent *OtherComponent, int32 OtherBodyIndex,
			bool bFromSweep, const FHitResult &SweepResult);
	UFUNCTION()
		void OnOverlapRedCr(UPrimitiveComponent* OverlappedComponent, AActor *OtherActor,
			UPrimitiveComponent *OtherComponent, int32 OtherBodyIndex,
			bool bFromSweep, const FHitResult &SweepResult);

	UFUNCTION()
		void OnOverlapKey(UPrimitiveComponent* OverlappedComponent, AActor *OtherActor,
			UPrimitiveComponent *OtherComponent, int32 OtherBodyIndex,
			bool bFromSweep, const FHitResult &SweepResult);
	UFUNCTION()
		void OnOverlapEntrance(UPrimitiveComponent* OverlappedComponent, AActor *OtherActor,
			UPrimitiveComponent *OtherComponent, int32 OtherBodyIndex,
			bool bFromSweep, const FHitResult &SweepResult);

	bool Message{ false };
	FString MessageText{ "" };

	//[0] = blå, [1] = grønn, [2] = rosa, og [3] = rød.
	bool Crystals[4];

	//[0] = blå, [1] = grønn, [2] = rosa, og [3] = rød.
	bool Container[4];

	//[0] = blå, [1] = grønn, [2] = rosa, og [3] = rød.
	bool Taken[4];

	bool ContainerOn{ false };
	int ContainerNum;

	FVector ContainerPos;
	FVector KeyPos;

	AActor *MyPlayer = nullptr;

	float Timer{ 0.f };
	float Time{ 2.f };

	bool Finished{ false };
	int Working = -1;

	UPROPERTY(EditAnywhere, Category = "Krystall")
		FString Blue;
	UPROPERTY(EditAnywhere, Category = "Krystall")
		FString Green;
	UPROPERTY(EditAnywhere, Category = "Krystall")
		FString Pink;
	UPROPERTY(EditAnywhere, Category = "Krystall")
		FString Red;
};
