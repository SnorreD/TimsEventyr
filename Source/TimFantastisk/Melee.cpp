// Fill out your copyright notice in the Description page of Project Settings.

#include "TimFantastisk.h"
#include "Melee.h"
#include "Fiende.h"


// Sets default values
AMelee::AMelee()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("MySword"));
	RootComponent = RootCapsule;
	RootCapsule->SetRelativeScale3D(FVector(1.5f, 1.5f, 1.5f));
	RootCapsule->bGenerateOverlapEvents = true;
	RootCapsule->OnComponentBeginOverlap.AddDynamic(this, &AMelee::OnOverlap);

}

// Called when the game starts or when spawned
void AMelee::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMelee::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TimeLived += DeltaTime;
	if (TimeLived > TimeBeforeDestroy)
	{
		this->Destroy();
	}

}

void AMelee::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor *OtherActor,
	UPrimitiveComponent *OtherComponent, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult &SweepResult)
{
	//UE_LOG(LogTemp, Warning, TEXT("Bullet Overlap %s"), *OtherActor->GetName())
	if (OtherActor->IsA(AFiende::StaticClass()))
	{
		Cast<AFiende>(OtherActor)->ImHit(1.f); //Alternativt bare OtherActor->Destroy();
											//PartikkelFX:
											//UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplotionFX, GetTransform(), true);

											//SoundFX
											//UGameplayStatics::PlaySound2D(GetWorld(), ExplotionSound, 1.f, 1.f, 0.f);
											//UGameplayStatics::PlaySoundAtLocation(GetWorld(), ExplotionSound, GetActorLocation());

											//Destroy Bullet:
		Destroy();
	}
}

