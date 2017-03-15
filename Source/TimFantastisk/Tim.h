// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "Tim.generated.h"

UCLASS()
class TIMFANTASTISK_API ATim : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATim();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	/** Returns CursorToWorld subobject **/
	//FORCEINLINE class UDecalComponent* GetCursorToWorld() { return CursorToWorld; }

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveX(float AxisValue);
	void MoveY(float AxisValue);
	void Jump();
	void Attack();
	void Modus1();
	void Modus2();
	void Modus3();
	void ImHit();

	FVector CurrentVelocity;
	int Mode;

	UPROPERTY(EditAnywhere)
		int Speed = 400;

	UPROPERTY(EditAnywhere)
		USceneComponent* OurVisibleComponent;

	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UDecalComponent* CursorToWorld;

	UPROPERTY(EditAnywhere, Category = "Spawning")
		TSubclassOf<class ABullet> BulletBlueprint;
	UPROPERTY(EditAnywhere, Category = "Spawning")
		TSubclassOf<class AMelee> MeleeBlueprint;

	bool Skytesperre{ false };

	UPROPERTY(EditAnywhere)
		float AngrepMellomrom = 0.5f;

	float TidSidenAngrep;
};
