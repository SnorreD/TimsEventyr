// Fill out your copyright notice in the Description page of Project Settings.

#include "TimFantastisk.h"
#include "ChangeCameraAngle.h"
#include "Tim.h"




AChangeCameraAngle::AChangeCameraAngle()
{
	PrimaryActorTick.bCanEverTick = true;

	PrimaryActorTick.bCanEverTick = true;
	RootCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("MyEnemy"));
	RootComponent = RootCapsule;
	RootCapsule->bGenerateOverlapEvents = true;
	RootCapsule->OnComponentBeginOverlap.AddDynamic(this, &AChangeCameraAngle::OnOverlap);

}

void AChangeCameraAngle::BeginPlay()
{
	Super::BeginPlay();
	
}

void AChangeCameraAngle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AChangeCameraAngle::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor *OtherActor,
	UPrimitiveComponent *OtherComponent, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult &SweepResult)
{
	//Hvis spilleren kommer borti denne blir kameraet forandret basert på 'ArmLenght' og 'CameraRotation' variablen, før den ødelgger seg selv.
	if (OtherActor->IsA(ATim::StaticClass()))
	{
		USpringArmComponent *Camera = Cast<ATim>(OtherActor)->CameraBoom;
		Camera->TargetArmLength = ArmLenght;
		Camera->RelativeRotation = CameraRotation;
	}
	Destroy();

}

