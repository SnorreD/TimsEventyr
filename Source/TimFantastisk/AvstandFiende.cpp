// Fill out your copyright notice in the Description page of Project Settings.

#include "TimFantastisk.h"
#include "AvstandFiende.h"
#include "Bullet.h"
#include "TimGameMode.h"


AAvstandFiende::AAvstandFiende()
{
	PrimaryActorTick.bCanEverTick = true;
	RootCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("MyEnemy"));
	RootComponent = RootCapsule;
	RootCapsule->SetSimulatePhysics(true);
	RootCapsule->SetSimulatePhysics(true);

	//Fienden sin fart.
	CurrentVelocity.X = 300.0f;
	CurrentVelocity.Y = 300.0f;

}

void AAvstandFiende::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAvstandFiende::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Hvis fienden er nærme nok og han ikke akkuratt har skutt en kule, så skyt.
	if (NewDirection.Size() < ShootDistance)
	{
		LastShot += DeltaTime;
		if (LastShot > TimeBetweenShots)
		{
			GetWorld()->SpawnActor<ABullet>(BulletBlueprint, GetActorLocation() + GetActorForwardVector() * 160.f, GetActorRotation());
			LastShot = 0.f;
		}
	}

	//Hvis fienden ikke er nærme nok til å skyte men nærme nok til å følge etter spilleren så gjør den det.
	else if (NewDirection.Size() < MoveDistance)
	{
		FVector NewLocation = GetActorLocation() + GetActorForwardVector()*(CurrentVelocity * DeltaTime);
		SetActorLocation(NewLocation);
	}

	//Finner spillerens plassering og roterer etter den.
	NewDirection = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetActorLocation() - GetActorLocation();
	NewDirection.Z = 0.f;
	SetActorRotation(NewDirection.Rotation());

	//Dreper fienden hvis han har falt utenfor kartet.
	if (GetActorLocation().Z < Cast<ATimGameMode>(GetWorld()->GetAuthGameMode())->KillZ)
	{
		Destroy();
	}

}

void AAvstandFiende::ImHit(float Damage)
{
	//Hvis fienden er truffet av noe tar den skade.
	Health = Health - Damage;

	//Fienden blir ødelagt hvis den går tom for liv.
	if (Health <= 0.f)
	{
		this->Destroy();
	}
}

