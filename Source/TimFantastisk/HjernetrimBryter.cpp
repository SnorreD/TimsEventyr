// Fill out your copyright notice in the Description page of Project Settings.

#include "TimFantastisk.h"
#include "HjernetrimBryter.h"
#include "Tim.h"


// Sets default values
AHjernetrimBryter::AHjernetrimBryter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PuzzleBox = CreateDefaultSubobject<UBoxComponent>(TEXT("PuzzleBox"));
	RootComponent = PuzzleBox;
	BryterBox = CreateDefaultSubobject<UBoxComponent>(TEXT("BryterBox"));
	BryterMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BryterMesh"));
	BryterMesh->SetupAttachment(BryterBox);
	
	BryterBox->bGenerateOverlapEvents = true;
	BryterBox->OnComponentBeginOverlap.AddDynamic(this, &AHjernetrimBryter::OnOverlap);

	Door = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door"));
	Door->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AHjernetrimBryter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHjernetrimBryter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (PlayerActivate)
	{
		StartTime += DeltaTime;
		if (StartTime < MoveTime)
			Door->SetWorldLocation(FVector(Door->GetComponentLocation().X, Door->GetComponentLocation().Y, Door->GetComponentLocation().Z - (MoveDistance/MoveTime)*DeltaTime));
	}

}

void AHjernetrimBryter::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor *OtherActor,
	UPrimitiveComponent *OtherComponent, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult &SweepResult)
{
	if (OtherActor->IsA(ATim::StaticClass()))
	{
		if (PlayerActivate == false)
		{
			PlayerActivate = true;
			if (DestroyHitBox)
				BryterMesh->DestroyComponent();
		}

	}
}

