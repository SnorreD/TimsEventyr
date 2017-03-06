// Fill out your copyright notice in the Description page of Project Settings.

#include "TimFantastisk.h"
#include "Fiende.h"
#include "Tim.h"


// Sets default values
AFiende::AFiende()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("MyEnemy"));
	RootComponent = RootCapsule;
	RootCapsule->SetSimulatePhysics(true);

	CurrentVelocity.X = 300.0f;
	CurrentVelocity.Y = 300.0f;
	//CurrentVelocity.Z = 300.0f;

}

// Called when the game starts or when spawned
void AFiende::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AFiende::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	if (!CurrentVelocity.IsZero())
	{
		if ((NewDirection.X < 600.0f && NewDirection.X > -600.0f) && (NewDirection.Y < 600.0f && NewDirection.Y > -600.0f))
		{
			FVector NewLocation = GetActorLocation() + GetActorForwardVector()*(CurrentVelocity * DeltaTime);
			SetActorLocation(NewLocation);
		}
		
	}

	ACharacter* myCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	FVector EnemyLocation = GetActorLocation();
	FVector PlayerLocation = myCharacter->GetActorLocation();
	NewDirection = PlayerLocation - EnemyLocation;
	NewDirection.Z = 0.f;
	SetActorRotation(NewDirection.Rotation());


}

void AFiende::ImHit()
{
	Destroy();
}

