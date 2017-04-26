// Fill out your copyright notice in the Description page of Project Settings.

#include "TimFantastisk.h"
#include "Boss1.h"
#include "Bullet.h"
#include "TimGameMode.h"


ABoss1::ABoss1()
{
	PrimaryActorTick.bCanEverTick = true;

	PrimaryActorTick.bCanEverTick = true;
	RootCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("MyEnemy"));
	RootComponent = RootCapsule;
	RootCapsule->SetSimulatePhysics(true);
	RootCapsule->SetSimulatePhysics(true);

}

void ABoss1::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABoss1::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Her byttes skyte modus etter en tilfeldig tid.
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

	//Hvis fienden er n�rme nok skyter han mot spilleren med en av to skytemoduser.
	if (NewDirection.Size() < ShootDistance)
	{
		LastShot += DeltaTime;
		if (LastShot > TimeBetweenShots)
		{
			//Skytemodus 1: skyter mange sm� kuler. Kulene tar lite skade.
			if (Mode == 1)
			{
				AActor* Bullet = GetWorld()->SpawnActor<ABullet>(BulletBlueprint, GetActorLocation() + GetActorForwardVector() * 120.f, FRotator(GetActorRotation().Pitch, GetActorRotation().Yaw - 25.f, GetActorRotation().Roll));
				Cast<ABullet>(Bullet)->Damage *= 0.5f;
				Bullet = GetWorld()->SpawnActor<ABullet>(BulletBlueprint, GetActorLocation() + GetActorForwardVector() * 250.f, GetActorRotation());
				Cast<ABullet>(Bullet)->Damage *= 0.5f;
				Bullet = GetWorld()->SpawnActor<ABullet>(BulletBlueprint, GetActorLocation() + GetActorForwardVector() * 120.f, FRotator(GetActorRotation().Pitch, GetActorRotation().Yaw + 25.f, GetActorRotation().Roll));
				Cast<ABullet>(Bullet)->Damage *= 0.5f;
				LastShot = 0.f;
			}
			//Skytemodus 2: skyter f� store kuler. Kulene tar mer skade.
			if (Mode == 2)
			{
				AActor *Bullet = GetWorld()->SpawnActor<ABullet>(BulletBlueprint, GetActorLocation() + GetActorForwardVector() * 160.f, GetActorRotation());
				Bullet->SetActorRelativeScale3D(FVector(3.f, 3.f, 3.f));
				Cast<ABullet>(Bullet)->Damage *= 2.f;
				LastShot = 0.f;
			}
			
		}

		//Dreper fienden hvis han har falt utenfor kartet.
		if (GetActorLocation().Z < Cast<ATimGameMode>(GetWorld()->GetAuthGameMode())->KillZ)
		{
			Destroy();
		}
	}

	//Finner spillerens plassering og roterer etter den.
	NewDirection = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetActorLocation() - GetActorLocation();
	NewDirection.Z = 0.f;
	SetActorRotation(NewDirection.Rotation());

}

void ABoss1::ImHit(float Damage)
{
	//Fienden tar skade hvis den er truffet. Er han tom for liv blir han �delagt.
	Health = Health - Damage;

	if (Health <= 0.f)
	{
		this->Destroy();
	}
}

