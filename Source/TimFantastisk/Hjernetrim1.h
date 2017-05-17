// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Hjernetrim1.generated.h"

UCLASS()
class TIMFANTASTISK_API AHjernetrim1 : public AActor
{
	GENERATED_BODY()
	
public:	

	AHjernetrim1();

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

	UFUNCTION()
		void EndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		bool PlayerActivate = false;

	//Lys og dems farge verdi. 1 = Rød, 2 = Oransje, 3 = Lilla og 4 = Blå.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Light, meta = (AllowPrivateAccess = "true"))
		int Light1 = 3;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Light, meta = (AllowPrivateAccess = "true"))
		int Light2 = 4;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Light, meta = (AllowPrivateAccess = "true"))
		int Light3 = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Light, meta = (AllowPrivateAccess = "true"))
		int Light4 = 2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Light, meta = (AllowPrivateAccess = "true"))
		bool Finished = false;

	UFUNCTION(BlueprintCallable, Category = Light)
		int ChangeLight(int x);
};
