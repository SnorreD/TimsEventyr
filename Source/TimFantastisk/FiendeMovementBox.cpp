// Fill out your copyright notice in the Description page of Project Settings.

#include "TimFantastisk.h"
#include "FiendeMovementBox.h"
#include "Hjernetrim2Fiende.h"


// Sets default values
AFiendeMovementBox::AFiendeMovementBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootBox = CreateDefaultSubobject<UBoxComponent>(TEXT("MySphere"));
	RootComponent = RootBox;
	RootBox->bGenerateOverlapEvents = true;
	RootBox->OnComponentBeginOverlap.AddDynamic(this, &AFiendeMovementBox::OnOverlap);
}

// Called when the game starts or when spawned
void AFiendeMovementBox::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFiendeMovementBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFiendeMovementBox::StartJump(AActor *OtherActor)
{
	Cast<AHjernetrim2Fiende>(OtherActor)->RootCapsule->AddImpulse(FVector(0.f, 0.f, 1.f * JumpHeight));
	Cast<AHjernetrim2Fiende>(OtherActor)->RootCapsule->AddImpulse(GetActorForwardVector() * 30000.f);
}

void AFiendeMovementBox::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor *OtherActor,
	UPrimitiveComponent *OtherComponent, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult &SweepResult)
{
	if (OtherActor->IsA(AHjernetrim2Fiende::StaticClass()))
	{
		if (Jump == EnemysCount || Jump == 5)
			StartJump(OtherActor);
		if (MoveToThis == EnemysCount || MoveToThis == 5)
			Cast<AHjernetrim2Fiende>(OtherActor)->SetActorRotation(GetActorRotation());
		if (Move180 == EnemysCount || Move180 == 5)
		{
			Cast<AHjernetrim2Fiende>(OtherActor)->TurnDegree = 180.f;
			Cast<AHjernetrim2Fiende>(OtherActor)->StartTurn = true;
		}
		if (Move90right == EnemysCount || Move90right == 5)
		{
			Cast<AHjernetrim2Fiende>(OtherActor)->TurnDegree = 90.f;
			Cast<AHjernetrim2Fiende>(OtherActor)->StartTurn = true;
		}
		if (Move90left == EnemysCount || Move90left == 5)
		{
			Cast<AHjernetrim2Fiende>(OtherActor)->TurnDegree = -90.f;
			Cast<AHjernetrim2Fiende>(OtherActor)->StartTurn = true;
		}

		if (FightAfter == EnemysCount || FightAfter == 5)
		{
			Cast<AHjernetrim2Fiende>(OtherActor)->Attack = true;
		}

		if (teleport == EnemysCount || teleport == 5)
		{
			OtherActor->SetActorLocation(tele);
		}

		if (DestroyAfter == EnemysCount)
			Destroy();

		++EnemysCount;
	}
}

