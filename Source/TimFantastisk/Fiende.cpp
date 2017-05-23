// Fill out your copyright notice in the Description page of Project Settings.

#include "TimFantastisk.h"
#include "Fiende.h"
#include "Tim.h"
#include "Bullet.h"
#include "TimGameMode.h"


AFiende::AFiende()
{
	PrimaryActorTick.bCanEverTick = true;

	RootSphere = CreateDefaultSubobject<USphereComponent>(TEXT("HitBox"));
	RootSphere->bGenerateOverlapEvents = true;
	RootSphere->OnComponentBeginOverlap.AddDynamic(this, &AFiende::OnOverlap);
	RootSphere->AttachToComponent(RootComponent, FAttachmentTransformRules(EAttachmentRule::KeepRelative, true));
}

void AFiende::BeginPlay()
{
	Super::BeginPlay();

}

void AFiende::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Har fienden nylig blitt angrepet eller angrepi?
	//Hvis ja hopper den opp og går bakover.

	if (Faen == true || Angrep == true)
		HitBack(DeltaTime);

	//Følger etter spilleren hvis spilleren er nær nok.
	if (NewDirection.Size() < AttackDistance && !Dead)
	{
		AddMovementInput(GetActorForwardVector(), Direction);
		Walking = true;
		if (NewDirection.Size() < 150.f)
			Attacking = true;
		else
			Attacking = false;
	}
		

	//Finner spillerens posisjon og roterer seg mot spilleren
	if (UGameplayStatics::GetPlayerCharacter(GetWorld(), 0) && !Dead)
	{
		NewDirection = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetActorLocation() - GetActorLocation();
		NewDirection.Z = 0.f;
		SetActorRotation(NewDirection.Rotation());
	}

	//Dreper fienden hvis han har falt utenfor kartet.
	if (GetActorLocation().Z < Cast<ATimGameMode>(GetWorld()->GetAuthGameMode())->KillZ)
	{
		Destroy();
	}

	if (Dead)
	{
		Timer += DeltaTime;
		if (Timer > DeadTime)
			Destroy();
	}

}

//Hvis den er skadet og ikke har blitt skadet i nær tid, tar den skade og hopper bakover.
void AFiende::ImHit(float Damage)
{
	Health = Health - Damage;

	if (Health <= 0.f)
	{
		Dead = true;
	}

	Faen = true;
}

void AFiende::HitBack(float DeltaTime)
{
	if (Direction > 0)
	{
		Direction = -0.5f;
		Jump();
	}

	LastHit += DeltaTime;
	if (LastHit > HitBackTime)
	{
		if (Faen)
			Faen = false;
		else
			Angrep = false;

		Direction = 1.f;
		LastHit = 0.f;
	}
}

void AFiende::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor *OtherActor,
	UPrimitiveComponent *OtherComponent, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult &SweepResult)
{
	//Hvis fienden rører spilleren tar den et liv fra spilleren.
	if (OtherActor->IsA(ATim::StaticClass()) && !Dead)
	{
		if (Faen == false)
		{
			Cast<ATim>(OtherActor)->ImHit(1.f);
			Angrep = true;
		}
	}
}
