// Fill out your copyright notice in the Description page of Project Settings.

#include "TimFantastisk.h"
#include "Rope.h"
#include "Tim.h"


// Tauet fungerer som en heis.
ARope::ARope()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootBox = CreateDefaultSubobject<UBoxComponent>(TEXT("MyBox"));
	RootComponent = RootBox;
	RootBox->bGenerateOverlapEvents = true;
	RootBox->OnComponentBeginOverlap.AddDynamic(this, &ARope::OnOverlap);

	LiftBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Elevator"));
	LiftBox->SetRelativeScale3D(FVector(2.f, 2.f, 0.02f));
	LiftBox->SetupAttachment(RootComponent);
	LiftBox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	LiftBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
}

// Called when the game starts or when spawned
void ARope::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARope::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (Velocity != 0.f && (LiftBox->GetComponentLocation().Z <= MaxHeight || Velocity < 0) && (LiftBox->GetComponentLocation().Z >= MinHeight || Velocity > 0))
	{
		FVector NewLocation = LiftBox->GetComponentLocation() + FVector(0.f, 0.f, 1.f)*(Velocity * DeltaTime);
		LiftBox->SetWorldLocation(NewLocation);
	}
}

//Setter haisboksen under spilleren nå spilleren rører tauet.
void ARope::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor *OtherActor,
	UPrimitiveComponent *OtherComponent, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult &SweepResult)
{
	if (OtherActor->IsA(ATim::StaticClass()))
	{
		Cast<ATim>(OtherActor)->Rope = this;
		Cast<ATim>(OtherActor)->Climbing = true;
		LiftBox->SetWorldLocation(OtherActor->GetActorLocation() - FVector(0.f, 0.f, 100.f));
	}
}