// Fill out your copyright notice in the Description page of Project Settings.

#include "TimFantastisk.h"
#include "AvstandFiende.h"
#include "Bullet.h"


// Sets default values
AAvstandFiende::AAvstandFiende()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CurrentVelocity.X = 300.0f;
	CurrentVelocity.Y = 300.0f;

}

// Called when the game starts or when spawned
void AAvstandFiende::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAvstandFiende::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!CurrentVelocity.IsZero())
	{
		if ((NewDirection.X < 400.0f && NewDirection.X > -400.0f) && (NewDirection.Y < 400.0f && NewDirection.Y > -400.0f))
		{
			LastShot += DeltaTime;
			if (LastShot > TimeBetweenShots)
			{
				GetWorld()->SpawnActor<ABullet>(BulletBlueprint, GetActorLocation() + GetActorForwardVector() * 100.f, GetActorRotation());
				LastShot = 0.f;
			}	
		}

		else if ((NewDirection.X < 800.0f && NewDirection.X > -800.0f) && (NewDirection.Y < 800.0f && NewDirection.Y > -800.0f))
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

