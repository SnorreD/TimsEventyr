// Fill out your copyright notice in the Description page of Project Settings.

#include "TimFantastisk.h"
#include "Fiende.h"
#include "Tim.h"
#include "Bullet.h"


// Sets default values
AFiende::AFiende()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("MyEnemy"));
	RootComponent = RootCapsule;
	RootCapsule->SetSimulatePhysics(true);
	RootCapsule->bGenerateOverlapEvents = true;
	RootCapsule->OnComponentBeginOverlap.AddDynamic(this, &AFiende::OnOverlap);

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

	if (Faen == true)
	{
		for (float TimeHit = 0.f; TimeHit < HitBackTime; ++TimeHit)
		{
			FVector LocationWhenHit = GetActorLocation();
			LocationWhenHit.Z = LocationWhenHit.Z + 20.f;
			SetActorLocation(LocationWhenHit);
		};
		Faen = false;
	}

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

void AFiende::ImHit(float Damage)
{
	if (Faen == false)
	{
		Health = Health - Damage;

		if (Health <= 0.f)
		{
			this->Destroy();
		}
	}
	
	Damage = 0;
	Faen = true;
}

void AFiende::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor *OtherActor,
	UPrimitiveComponent *OtherComponent, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult &SweepResult)
{
	//UE_LOG(LogTemp, Warning, TEXT("Bullet Overlap %s"), *OtherActor->GetName())
	if (OtherActor->IsA(ATim::StaticClass()))
	{
		Cast<ATim>(OtherActor)->ImHit(); //Alternativt bare OtherActor->Destroy();
												//PartikkelFX:
												//UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplotionFX, GetTransform(), true);

												//SoundFX
												//UGameplayStatics::PlaySound2D(GetWorld(), ExplotionSound, 1.f, 1.f, 0.f);
												//UGameplayStatics::PlaySoundAtLocation(GetWorld(), ExplotionSound, GetActorLocation());
	}
}
