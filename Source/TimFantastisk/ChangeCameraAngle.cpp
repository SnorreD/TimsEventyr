// Fill out your copyright notice in the Description page of Project Settings.

#include "TimFantastisk.h"
#include "ChangeCameraAngle.h"
#include "Tim.h"




// Sets default values
AChangeCameraAngle::AChangeCameraAngle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PrimaryActorTick.bCanEverTick = true;
	RootCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("MyEnemy"));
	RootComponent = RootCapsule;
	RootCapsule->bGenerateOverlapEvents = true;
	RootCapsule->OnComponentBeginOverlap.AddDynamic(this, &AChangeCameraAngle::OnOverlap);

}

// Called when the game starts or when spawned
void AChangeCameraAngle::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AChangeCameraAngle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AChangeCameraAngle::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor *OtherActor,
	UPrimitiveComponent *OtherComponent, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult &SweepResult)
{
	if (OtherActor->IsA(ATim::StaticClass()))
	{
		USpringArmComponent *Camera = Cast<ATim>(OtherActor)->CameraBoom;
		Camera->TargetArmLength = ArmLenght;
		Camera->RelativeRotation = CameraRotation;
	}
	Destroy();

}

