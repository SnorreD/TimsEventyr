// Fill out your copyright notice in the Description page of Project Settings.

#include "TimFantastisk.h"
#include "AvstandFiende.h"
#include "Bullet.h"


// Sets default values
AAvstandFiende::AAvstandFiende()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("MyEnemy"));
	RootComponent = RootCapsule;
	RootCapsule->SetSimulatePhysics(true);
	RootCapsule->SetSimulatePhysics(true);

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
		if ((NewDirection.X < ShootDistance && NewDirection.X > (ShootDistance * -1)) && (NewDirection.Y < ShootDistance && NewDirection.Y > (ShootDistance * -1)))
		{
			LastShot += DeltaTime;
			if (LastShot > TimeBetweenShots)
			{
				GetWorld()->SpawnActor<ABullet>(BulletBlueprint, GetActorLocation() + GetActorForwardVector() * 155.f, GetActorRotation());
				LastShot = 0.f;
			}
		}
	}

	else if ((NewDirection.X < MoveDistance && NewDirection.X > (MoveDistance * -1)) && (NewDirection.Y < MoveDistance && NewDirection.Y > (MoveDistance * -1)))
	{
		FVector NewLocation = GetActorLocation() + GetActorForwardVector()*(CurrentVelocity * DeltaTime);
		SetActorLocation(NewLocation);
	}

	ACharacter* myCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	FVector EnemyLocation = GetActorLocation();
	FVector PlayerLocation = myCharacter->GetActorLocation();
	NewDirection = PlayerLocation - EnemyLocation;
	NewDirection.Z = 0.f;
	SetActorRotation(NewDirection.Rotation());

}

void AAvstandFiende::ImHit(float Damage)
{
	Health = Health - Damage;

	if (Health <= 0.f)
	{
		this->Destroy();
	}

	Damage = 0;
	//Faen = true;
}

