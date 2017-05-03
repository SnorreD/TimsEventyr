// Fill out your copyright notice in the Description page of Project Settings.

#include "TimFantastisk.h"
#include "Boss1.h"
#include "Bullet.h"
#include "TimGameMode.h"
#include "Fiende.h"
#include "LevelUp.h"


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
			Mode = 3;
			TimeBetweenShots = 0.1f;
		}
		else if (Mode == 3)
		{
			Mode = 4;
			TimeBetweenShots = 1.2f;
		}
		else if (Mode == 4)
			Mode = 5;

		else if (Mode == 5)
		{
			Mode = 1;
			TimeBetweenShots = 0.2f;
		}

		TimeSinceModeChange = 0.f;
		ModeChangeTime = FMath::FRandRange(5.f, 10.f);
	}

	//Hvis fienden er nærme nok skyter han mot spilleren med en av to skytemoduser.
	if (NewDirection.Size() < ShootDistance)
	{
		LastShot += DeltaTime;
		if (LastShot > TimeBetweenShots)
		{
			//Skytemodus 1: skyter mange små kuler. Kulene tar lite skade.
			if (Mode == 1)
			{
				AActor* Bullet = GetWorld()->SpawnActor<ABullet>(BulletBlueprint, GetActorLocation() + GetActorForwardVector() * 120.f, FRotator(GetActorRotation().Pitch, GetActorRotation().Yaw - 25.f, GetActorRotation().Roll));
				Bullet = GetWorld()->SpawnActor<ABullet>(BulletBlueprint, GetActorLocation() + GetActorForwardVector() * 120.f, GetActorRotation());
				Bullet = GetWorld()->SpawnActor<ABullet>(BulletBlueprint, GetActorLocation() + GetActorForwardVector() * 120.f, FRotator(GetActorRotation().Pitch, GetActorRotation().Yaw + 25.f, GetActorRotation().Roll));

				LastShot = 0.f;
			}
			//Skytemodus 2: skyter få store kuler. Kulene tar mer skade.
			else if (Mode == 2)
			{
				AActor *Bullet = GetWorld()->SpawnActor<ABullet>(BulletBlueprint, GetActorLocation() + GetActorForwardVector() * 160.f, GetActorRotation());
				if (Bullet)
				{
					Bullet->SetActorRelativeScale3D(FVector(3.f, 3.f, 3.f));
					Cast<ABullet>(Bullet)->Damage *= 2.f;
				}

				LastShot = 0.f;
			}
			//Skytemodus 3: skyter mellom store kuler i tilfeldig retning. Kulene gjør normalt med skade.
			else if (Mode == 3)
			{
				AActor *Bullet = GetWorld()->SpawnActor<ABullet>(BulletBlueprint, GetActorLocation(), FRotator(GetActorRotation().Pitch, GetActorRotation().Yaw + FMath::FRandRange(-50.f, 50.f), GetActorRotation().Roll));
				if (Bullet)
					Bullet->SetActorRelativeScale3D(FVector(1.7f, 1.7f, 1.7f));

				LastShot = 0.f;
			}
			else if (Mode == 4)
			{
				AActor *Fiende = GetWorld()->SpawnActor<AFiende>(FiendeBlueprint, GetActorLocation() + GetActorForwardVector() * 180.f, FRotator(90.f, 0.f, 0.f));
				if (Fiende)
					Cast<AFiende>(Fiende)->AttackDistance = ShootDistance;

				LastShot = 0.f;
			}
			
		}

		//Dreper fienden hvis han har falt utenfor kartet.
		if (GetActorLocation().Z < Cast<ATimGameMode>(GetWorld()->GetAuthGameMode())->KillZ)
		{
			ABoss1::ImHit(50.f);
		}
	}

	//Finner spillerens plassering og roterer etter den.
	NewDirection = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetActorLocation() - GetActorLocation();
	NewDirection.Z = 0.f;
	SetActorRotation(NewDirection.Rotation());

}

void ABoss1::ImHit(float Damage)
{
	//Fienden tar skade hvis den er truffet. Er han tom for liv blir han ødelagt.
	Health = Health - Damage;

	if (Health <= 0.f)
	{
		if (PowerDropLevel > 0)
		{
			AActor *Power = GetWorld()->SpawnActor<ALevelUp>(PowerDrop, GetActorLocation(), GetActorRotation());
			Cast<ALevelUp>(Power)->Level = PowerDropLevel;
			Cast<ALevelUp>(Power)->Info = PowerDropInfo;
		}
		
		this->Destroy();
	}
}

