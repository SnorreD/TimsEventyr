// Fill out your copyright notice in the Description page of Project Settings.

#include "TimFantastisk.h"
#include "Boss1.h"
#include "Bullet.h"


// Sets default values
ABoss1::ABoss1()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PrimaryActorTick.bCanEverTick = true;
	RootCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("MyEnemy"));
	RootComponent = RootCapsule;
	RootCapsule->SetSimulatePhysics(true);
	RootCapsule->SetSimulatePhysics(true);

}

// Called when the game starts or when spawned
void ABoss1::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABoss1::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TimeSinceModeChange += DeltaTime;
	if (TimeSinceModeChange > ModeChangeTime)
	{
		if (Mode == 1)
		{
			Mode = 2;
			TimeBetweenShots = 0.8f;
		}
		else if (Mode == 2)
		{
			Mode = 1;
			TimeBetweenShots = 0.2f;
		}
		TimeSinceModeChange = 0.f;
		ModeChangeTime = FMath::FRandRange(10.f, 20.f);
	}

	if ((NewDirection.X < ShootDistance && NewDirection.X >(ShootDistance * -1)) && (NewDirection.Y < ShootDistance && NewDirection.Y >(ShootDistance * -1)))
	{
		LastShot += DeltaTime;
		if (LastShot > TimeBetweenShots)
		{
			if (Mode == 1)
			{
				GetWorld()->SpawnActor<ABullet>(BulletBlueprint, GetActorLocation() + GetActorForwardVector() * 120.f, FRotator(GetActorRotation().Pitch, GetActorRotation().Yaw - 25.f, GetActorRotation().Roll));
				GetWorld()->SpawnActor<ABullet>(BulletBlueprint, GetActorLocation() + GetActorForwardVector() * 250.f, GetActorRotation());
				GetWorld()->SpawnActor<ABullet>(BulletBlueprint, GetActorLocation() + GetActorForwardVector() * 120.f, FRotator(GetActorRotation().Pitch, GetActorRotation().Yaw + 25.f, GetActorRotation().Roll));
				LastShot = 0.f;
			}
			if (Mode == 2)
			{
				AActor *Bullet = GetWorld()->SpawnActor<ABullet>(BulletBlueprint, GetActorLocation() + GetActorForwardVector() * 160.f, GetActorRotation());
				Bullet->SetActorRelativeScale3D(FVector(3.f, 3.f, 3.f));
				LastShot = 0.f;
			}
			
		}
	}

	ACharacter* myCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	FVector EnemyLocation = GetActorLocation();
	FVector PlayerLocation = myCharacter->GetActorLocation();
	NewDirection = PlayerLocation - EnemyLocation;
	NewDirection.Z = 0.f;
	SetActorRotation(NewDirection.Rotation());

}

void ABoss1::ImHit(float Damage)
{
	Health = Health - Damage;

	if (Health <= 0.f)
	{
		this->Destroy();
	}

	Damage = 0;
	//Faen = true;
}

