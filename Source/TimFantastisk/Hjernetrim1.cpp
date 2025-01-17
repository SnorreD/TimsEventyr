// Fill out your copyright notice in the Description page of Project Settings.

#include "TimFantastisk.h"
#include "Hjernetrim1.h"
#include "Tim.h"

//Mye er gjort i blueprint her.

// Sets default values
AHjernetrim1::AHjernetrim1()
{
	PrimaryActorTick.bCanEverTick = true;

	RootBox = CreateDefaultSubobject<UBoxComponent>(TEXT("MyBox"));
	RootComponent = RootBox;
	RootBox->bGenerateOverlapEvents = true;
	RootBox->OnComponentBeginOverlap.AddDynamic(this, &AHjernetrim1::OnOverlap);
	RootBox->OnComponentEndOverlap.AddDynamic(this, &AHjernetrim1::EndOverlap);

}

void AHjernetrim1::BeginPlay()
{
	Super::BeginPlay();
	
}

void AHjernetrim1::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Hvis spilleren har fullf�rt g�ten blir den �delagt.
	if (PlayerActivate == true)
	{
		if (Light1 == 2 && Light2 == 1 && Light3 == 3 && Light4 == 4)
		{
			Finished = true;
		}
	}

}

int AHjernetrim1::ChangeLight(int x)
{
	//Forandrer lyset n�r man trykker p� en knapp i blueprint.
	if (!Finished)
	{
		if (x < 4)
			x++;
		else
			x = 1;
	}
	return x;
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
			Cast<ATim>(OtherActor)->Puzzle = this;
		}
		
	}
}

void AHjernetrim1::EndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->IsA(ATim::StaticClass()))
	{
		PlayerActivate = false;
		Cast<ATim>(OtherActor)->Puzzle = NULL;
	}
}

