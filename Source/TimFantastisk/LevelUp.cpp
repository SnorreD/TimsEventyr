// Fill out your copyright notice in the Description page of Project Settings.

#include "TimFantastisk.h"
#include "LevelUp.h"
#include "Tim.h"
#include "TimGameMode.h"


// Sets default values
ALevelUp::ALevelUp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootBox = CreateDefaultSubobject<UBoxComponent>(TEXT("MySphere"));
	RootComponent = RootBox;

	RootBox->bGenerateOverlapEvents = true;
	RootBox->OnComponentBeginOverlap.AddDynamic(this, &ALevelUp::OnOverlap);
	RootBox->OnComponentEndOverlap.AddDynamic(this, &ALevelUp::EndOverlap);

	OurVisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OurVisibleComponent"));
	OurVisibleComponent->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ALevelUp::BeginPlay()
{
	Super::BeginPlay();

	
}

// Called every frame
void ALevelUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//Gir spilleren en ny kraft, og en melding.
void ALevelUp::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor *OtherActor,
	UPrimitiveComponent *OtherComponent, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult &SweepResult)
{
	if (OtherActor->IsA(ATim::StaticClass()))
	{
		Cast<ATim>(OtherActor)->Level = Level;
		auto CurrentGameMode = Cast<ATimGameMode>(GetWorld()->GetAuthGameMode());
		CurrentGameMode->Tips = Info;
		OurVisibleComponent->DestroyComponent();
	}
}
//Fjerner meldingen.
void ALevelUp::EndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->IsA(ATim::StaticClass()))
	{
		auto CurrentGameMode = Cast<ATimGameMode>(GetWorld()->GetAuthGameMode());
		CurrentGameMode->Tips = "";
		Destroy();
	}
}