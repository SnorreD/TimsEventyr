// Fill out your copyright notice in the Description page of Project Settings.

#include "TimFantastisk.h"
#include "EnemySpawn.h"
#include "Fiende.h"
#include "AvstandFiende.h"
#include "Tim.h"


AEnemySpawn::AEnemySpawn()
{
	PrimaryActorTick.bCanEverTick = true;

	RootSphere = CreateDefaultSubobject<USphereComponent>(TEXT("MySphere"));
	RootComponent = RootSphere;

}

void AEnemySpawn::BeginPlay()
{
	Super::BeginPlay();
	
}

void AEnemySpawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Finner spillerens plassering og roterer etter den.
	FVector Distance = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetActorLocation() - GetActorLocation();
	Distance.Z = 0.f;

	//Sjekker om spilleren er nær.
	if (Distance.Size() < SpawnDistance)
	{
		PlayerClose = true;
	}

	//Hvis spilleren er nær gyter den ut fiender med en forsinkelse mellom.
	if (PlayerClose == true)
	{
		LastSpawn += DeltaTime;
		if (LastSpawn > TimeBetweenSpawned)
		{
			if (CloseRangeEnemy == true)
			{
				AActor *Fiende = GetWorld()->SpawnActor<AFiende>(FiendeBlueprint, GetActorLocation(), FRotator(90.f, 0.f, 0.f));
				LastSpawn = 0.f;
				++AmountSpawned;
				if (Fiende)
					Cast<AFiende>(Fiende)->AttackDistance = EnemyAttackDistance;
			}
			else
			{
				AActor *Fiende = GetWorld()->SpawnActor<AAvstandFiende>(AvstandFiendeBlueprint, GetActorLocation() + FVector(1.f, 0.f, 0.f) * 100.f, FRotator(90.f, 0.f, 0.f));
				LastSpawn = 0.f;
				++AmountSpawned;
				if (Fiende)
					Cast<AAvstandFiende>(Fiende)->MoveDistance = EnemyAttackDistance;
			}
			if (Rand)
			{
				CloseRangeEnemy = FMath::RandBool();
			}
		}
	}
	

	//Når gyteren har gyte ut nok fiender ødelegges den.
	if (NumberOfEnemies <= AmountSpawned)
	{
		this->Destroy();
	}



}

