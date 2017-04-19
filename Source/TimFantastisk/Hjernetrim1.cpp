// Fill out your copyright notice in the Description page of Project Settings.

#include "TimFantastisk.h"
#include "Hjernetrim1.h"
#include "Tim.h"


// Sets default values
AHjernetrim1::AHjernetrim1()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootBox = CreateDefaultSubobject<UBoxComponent>(TEXT("MyBox"));
	RootComponent = RootBox;
	RootBox->bGenerateOverlapEvents = true;
	RootBox->OnComponentBeginOverlap.AddDynamic(this, &AHjernetrim1::OnOverlap);
	RootBox->OnComponentEndOverlap.AddDynamic(this, &AHjernetrim1::EndOverlap);

}

// Called when the game starts or when spawned
void AHjernetrim1::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHjernetrim1::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (PlayerActivate == true)
	{
		if (Light1 == 3 && Light2 == 1 && Light3 == 2 && Light4 == 4)
		{
			PlayerActivate = false;
			Destroy();
		}
	}

}

void AHjernetrim1::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor *OtherActor,
	UPrimitiveComponent *OtherComponent, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult &SweepResult)
{
	if (OtherActor->IsA(ATim::StaticClass()))
	{
		if (PlayerActivate == false)
		{
			PlayerActivate = true;
			GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;
			GetWorld()->GetFirstPlayerController()->bEnableClickEvents = true;
			GetWorld()->GetFirstPlayerController()->bEnableMouseOverEvents = true;
			//GetWorld()->GetFirstPlayerController()->bEnableTouchEvents = true;
			Cast<ATim>(OtherActor)->Puzzle = this;
		}
		//GetWorld()->GetFirstPlayerController()->bShowMouseCursor = false;
		//GetWorld()->GetFirstPlayerController()->bEnableClickEvents = false;
		//GetWorld()->GetFirstPlayerController()->bEnableMouseOverEvents = false;
		//GetWorld()->GetFirstPlayerController()->bEnableTouchEvents = true;
		
	}
}

void AHjernetrim1::EndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->IsA(ATim::StaticClass()))
	{
		PlayerActivate = false;
		GetWorld()->GetFirstPlayerController()->bShowMouseCursor = false;
		GetWorld()->GetFirstPlayerController()->bEnableClickEvents = false;
		GetWorld()->GetFirstPlayerController()->bEnableMouseOverEvents = false;
		GetWorld()->GetFirstPlayerController()->bEnableTouchEvents = true;
		Cast<ATim>(OtherActor)->Puzzle = NULL;
	}
}

