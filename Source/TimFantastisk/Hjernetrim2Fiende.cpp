// Fill out your copyright notice in the Description page of Project Settings.

#include "TimFantastisk.h"
#include "Hjernetrim2Fiende.h"
#include "Bullet.h"


//Denne fienden brukes i samsvar med FiendeMovementBox.


// Sets default values
AHjernetrim2Fiende::AHjernetrim2Fiende()
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
void AHjernetrim2Fiende::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AHjernetrim2Fiende::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Hvis den ikke skal snu seg eller angrepe går den rett fram.
	if (StartTurn)
		Turn(DeltaTime);
	else if (Attack)
		StartAttacking(DeltaTime);
	else
	{
		FVector NewLocation = GetActorLocation() + GetActorForwardVector()*(CurrentSpeed * DeltaTime);
		SetActorLocation(NewLocation);
	}

	if (FiendeTag)
	{
		Timer += DeltaTime;
		if (Timer > 0.2f)
		{
			FiendeTag = false;
			Timer = 0.f;
		}
	}

}

//Snur seg basert på gradene den skal snu seg.
void AHjernetrim2Fiende::Turn(float DeltaTime)
{
	TimeSinceTurn += DeltaTime;
	if (TurnTime > TimeSinceTurn)
		SetActorRotation(FRotator(GetActorRotation().Pitch, GetActorRotation().Yaw + (TurnDegree*DeltaTime), GetActorRotation().Roll));
	else
	{
		TimeSinceTurn = 0.f;
		StartTurn = false;
	}
}

//Start å angrepe når den er bedt om det.
void AHjernetrim2Fiende::StartAttacking(float DeltaTime)
{
	FVector NewDirection = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetActorLocation() - GetActorLocation();
	NewDirection.Z = 0.f;
	SetActorRotation(NewDirection.Rotation());

	if (NewDirection.Size() < ShootDistance)
	{
		LastShot += DeltaTime;
		//Angreps modus blir valgt, en til hver av de 4.
		switch (AttackMode)
		{
			//Et sperreild av kuler.
		case 1:
			if (BarrageCounter >= 10)
			{
				if (LastShot > (TimeBetweenShots * 10))
					BarrageCounter = 0;
			}
			else if (LastShot > TimeBetweenShots)
			{
				GetWorld()->SpawnActor<ABullet>(BulletBlueprint, GetActorLocation(), GetActorRotation());
				LastShot = 0.f;
				++BarrageCounter;
			}
			break;
			//En hagle effekt av kuler.
		case 2:
			if (LastShot > TimeBetweenShots)
			{
				GetWorld()->SpawnActor<ABullet>(BulletBlueprint, GetActorLocation(), GetActorRotation());
				GetWorld()->SpawnActor<ABullet>(BulletBlueprint, GetActorLocation(), FRotator(GetActorRotation().Pitch, GetActorRotation().Yaw + 10.f, GetActorRotation().Roll));
				GetWorld()->SpawnActor<ABullet>(BulletBlueprint, GetActorLocation(), FRotator(GetActorRotation().Pitch, GetActorRotation().Yaw - 10.f, GetActorRotation().Roll));
				GetWorld()->SpawnActor<ABullet>(BulletBlueprint, GetActorLocation(), FRotator(GetActorRotation().Pitch, GetActorRotation().Yaw + 20.f, GetActorRotation().Roll));
				GetWorld()->SpawnActor<ABullet>(BulletBlueprint, GetActorLocation(), FRotator(GetActorRotation().Pitch, GetActorRotation().Yaw - 20.f, GetActorRotation().Roll));
				LastShot = 0.f;
			}
			break;
			// Vanlig raskt på med kuler.
		case 3:
			if (LastShot > TimeBetweenShots)
			{
				GetWorld()->SpawnActor<ABullet>(BulletBlueprint, GetActorLocation(), GetActorRotation());
				LastShot = 0.f;
			}
			break;
		}
	}
}

void AHjernetrim2Fiende::SetAttackMode(int Mode)
{
	//Når angrepesmodusen blir satt blir også hastigheten av angrepet satt basert på hvilket angrep den skal ha.
	switch (Mode)
	{
	case 1:
		TimeBetweenShots = 0.1f;
		break;
	case 2:
		TimeBetweenShots = 1.5f;
		break;
	case 3:
		TimeBetweenShots = 0.3f;
		break;
	}
	AttackMode = Mode;
}

void AHjernetrim2Fiende::ImHit(float Damage)
{
	//Hvis fienden er truffet av noe tar den skade.
	Health = Health - Damage;

	//Fienden blir ødelagt hvis den går tom for liv.
	if (Health <= 0.f)
	{
		this->Destroy();
	}
}
