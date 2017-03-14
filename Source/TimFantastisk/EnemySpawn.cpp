// Fill out your copyright notice in the Description page of Project Settings.

#include "TimFantastisk.h"
#include "EnemySpawn.h"
#include "Fiende.h"
#include "AvstandFiende.h"
#include "Tim.h"


// Sets default values
AEnemySpawn::AEnemySpawn()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootSphere = CreateDefaultSubobject<USphereComponent>(TEXT("MySphere"));
	RootComponent = RootSphere;

}

// Called when the game starts or when spawned
void AEnemySpawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemySpawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ACharacter* myCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	FVector EnemyLocation = GetActorLocation();
	FVector PlayerLocation = myCharacter->GetActorLocation();
	PlayerDistance = PlayerLocation - EnemyLocation;

	if ((PlayerDistance.X < 600.0f && PlayerDistance.X > -600.0f) && (PlayerDistance.Y < 600.0f && PlayerDistance.Y > -600.0f))
	{
		PlayerClose = true;
	}

	if (PlayerClose == true)
	{
		LastSpawn += DeltaTime;
		if (LastSpawn > TimeBetweenSpawned)
		{
			if (CloseRangeEnemy == true)
			{
				GetWorld()->SpawnActor<AFiende>(FiendeBlueprint, GetActorLocation() + FVector(1.f, 0.f, 0.f) * 100.f, FRotator(90.f, 0.f, 0.f));
				LastSpawn = 0.f;
				++AmountSpawned;
			}
			else
			{
				GetWorld()->SpawnActor<AAvstandFiende>(AvstandFiendeBlueprint, GetActorLocation() + FVector(1.f, 0.f, 0.f) * 100.f, FRotator(90.f, 0.f, 0.f));
				LastSpawn = 0.f;
				++AmountSpawned;
			}
			
		}
	}
	

	if (NumberOfEnemies <= AmountSpawned)
	{
		this->Destroy();
	}



}

