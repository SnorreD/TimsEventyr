// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Fiende.generated.h"

UCLASS()
class TIMFANTASTISK_API AFiende : public ACharacter
{
	GENERATED_BODY()

public:

	AFiende();

protected:

	virtual void BeginPlay() override;

public:

	virtual void Tick(float DeltaTime) override;

	FVector CurrentVelocity{ 300.f, 300.f, 0.f };
	FVector NewDirection;

	void ImHit(float Damage);

	//Sirkelen som tar skade på spilleren.
	UPROPERTY(EditAnywhere, Category = "Attack")
		UShapeComponent* RootSphere = nullptr;

	//Distansen den kan følge etter fienden.
	UPROPERTY(EditAnywhere, Category = "Attack")
		float AttackDistance = 900.f;

	float Health{ 2.f };

	//'Faen'og 'Angrep' dytter fienden tilbake hvis den har angrepi eller tatt skade.
	bool Faen{ false };
	bool Angrep{ false };

	//Variabler brukt til animasjon //////////////////
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		bool Walking = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		bool Attacking = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		bool Dead = false;
	////////////////////////////////////////////////////

	float HitBackTime{ 0.6f };
	float LastHit{ 0.f };

	float Direction = 1.f;

	void HitBack(float DeltaTime);

	float Timer{ 0.f };
	float DeadTime{ 1.208f };

	UFUNCTION()
		void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor *OtherActor,
			UPrimitiveComponent *OtherComponent, int32 OtherBodyIndex,
			bool bFromSweep, const FHitResult &SweepResult);


};
