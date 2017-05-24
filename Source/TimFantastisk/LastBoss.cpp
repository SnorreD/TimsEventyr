// Fill out your copyright notice in the Description page of Project Settings.

#include "TimFantastisk.h"
#include "LastBoss.h"
#include "Bullet.h"
#include "Fiende.h"
#include "AvstandFiende.h"
#include "Tim.h"
#include "TimGameMode.h"


// Sets default values
ALastBoss::ALastBoss()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("MyEnemy"));
	RootComponent = RootCapsule;
	RootCapsule->SetSimulatePhysics(true);
	RootCapsule->SetSimulatePhysics(true);

	PlatformBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Platform"));
	PlatformBox->SetupAttachment(RootComponent);
	PlatformBox->bGenerateOverlapEvents;
	PlatformBox->OnComponentBeginOverlap.AddDynamic(this, &ALastBoss::OnPlatform);

	RightHandCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("RightHand"));
	RightHandCapsule->SetupAttachment(RootComponent);
	RightHandCapsule->bGenerateOverlapEvents;
	RightHandCapsule->OnComponentBeginOverlap.AddDynamic(this, &ALastBoss::OnOverlap);

	LeftHandCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("LeftHand"));
	LeftHandCapsule->SetupAttachment(RootComponent);
	LeftHandCapsule->bGenerateOverlapEvents;
	LeftHandCapsule->OnComponentBeginOverlap.AddDynamic(this, &ALastBoss::OnOverlap);

}

// Called when the game starts or when spawned
void ALastBoss::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALastBoss::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//Bytter angreps modus basert på hvor mye liv han har igjen.
	if (Health < 6.2f)
	{
		Mode = 6;
		TimeBetweenShots = 1.5f;
	}
	else if (Health < 12.f)
	{
		Mode = 5;
		TimeBetweenShots = 0.1f;
		MeleeAttack = false;
		Attack1 = false;
		Attack2 = false;
		Moving = false;
	}
	else if (Health < 24.f)
	{
		Mode = 4;
		TimeBetweenShots = 1.f;
		
	}
	else if (Health < 36.f)
	{
		Mode = 3;
		TimeBetweenShots = 0.1f;
		Moving = false;
		MeleeAttack = false;
		Attack1 = false;
		Attack2 = false;
	}
	else if (Health < 48.f)
	{
		Mode = 2;
		TimeBetweenShots = 2.5f;
	}


	//Hvis fienden er nærme nok skyter han mot spilleren med en av to skytemoduser.
	if (Charge == true)
	{
		if (ChargeBullet)
		{

			BulletSize += DeltaTime / 2;
			ChargeBullet->SetActorRelativeScale3D(FVector(BulletSize * 2, BulletSize * 2, BulletSize * 2));
			if (BulletSize >= 2.5f)
			{
				Charge = false;
				BulletSize = 0.5f;
				if (ChargeBullet)
				{
					ChargeBullet->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
					Cast<ABullet>(ChargeBullet)->Speed = 1200.f;
					Cast<ABullet>(ChargeBullet)->TimeLived = 0.f;
					Cast<ABullet>(ChargeBullet)->TimeBeforeDestroy = 6.f;
					ChargeBullet = nullptr;
				}
			}
		}
	}
	if (MeleeAttack && LastShot >= 1.625f)
	{
		Attack1 = false;
		Attack2 = false;
		MeleeAttack = false;
	}
	LastShot += DeltaTime;
	if (LastShot > TimeBetweenShots)
	{
		//Skytemodus 1: skyter mange små kuler. Kulene tar lite skade.
		if (Mode == 1)
		{
			ChargeBullet = GetWorld()->SpawnActor<ABullet>(BulletBlueprint, GetActorLocation() + GetActorForwardVector() * 100.f, GetActorRotation());
			if (ChargeBullet)
			{
				ChargeBullet->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform, NAME_None);
				Cast<ABullet>(ChargeBullet)->Speed = 0.f;
				Cast<ABullet>(ChargeBullet)->TimeBeforeDestroy = 100.f;
				Cast<ABullet>(ChargeBullet)->StrongBullet = true;
				Charge = true;
			}
			LastShot = 0.f;
		}
		else if (Mode == 2)
		{
			MeleeAttack = true;
			Attack1 = true;
			LastShot = 0.f;
		}
		else if (Mode == 3)
		{
			AActor *Bullet = GetWorld()->SpawnActor<ABullet>(BulletBlueprint, GetActorLocation(), FRotator(GetActorRotation().Pitch, GetActorRotation().Yaw + FMath::FRandRange(-50.f, 50.f), GetActorRotation().Roll));
			if (Bullet)
			{
				Cast<ABullet>(Bullet)->TimeBeforeDestroy = 8.f;
				Bullet->SetActorRelativeScale3D(FVector(2.5f, 2.5f, 2.5f));
			}
				
			LastShot = 0.f;
		}
		else if (Mode == 4)
		{
			MeleeAttack = true;
			Attack2 = true;
			LastShot = 0.f;
		}
		else if (Mode == 5)
		{
			if (BarrageCounter >= 10)
			{
				if (LastShot > (TimeBetweenShots * 10))
					BarrageCounter = 0;
			}
			else if (LastShot > TimeBetweenShots)
			{
				AActor *Bullet = GetWorld()->SpawnActor<ABullet>(BulletBlueprint, GetActorLocation(), GetActorRotation());
				if (Bullet)
				{
					Cast<ABullet>(Bullet)->TimeBeforeDestroy = 5.f;
					Cast<ABullet>(Bullet)->Speed = 1200.f;
					Bullet->SetActorRelativeScale3D(FVector(2.5f, 2.5f, 2.5f));
				}
				LastShot = 0.f;
				++BarrageCounter;
			}
		}
		else if (Mode == 6 && !Dead)
		{
			AActor *Bullet = GetWorld()->SpawnActor<ABullet>(BulletBlueprint, GetActorLocation(), GetActorRotation());
			if (Bullet)
			{
				Cast<ABullet>(Bullet)->TimeBeforeDestroy = 8.f;
				Bullet->SetActorRelativeScale3D(FVector(2.5f, 2.5f, 2.5f));
			}
			Bullet = GetWorld()->SpawnActor<ABullet>(BulletBlueprint, GetActorLocation(), FRotator(GetActorRotation().Pitch, GetActorRotation().Yaw + 10.f, GetActorRotation().Roll));
			if (Bullet)
			{
				Cast<ABullet>(Bullet)->TimeBeforeDestroy = 8.f;
				Bullet->SetActorRelativeScale3D(FVector(2.5f, 2.5f, 2.5f));
			}
			Bullet = GetWorld()->SpawnActor<ABullet>(BulletBlueprint, GetActorLocation(), FRotator(GetActorRotation().Pitch, GetActorRotation().Yaw - 10.f, GetActorRotation().Roll));
			if (Bullet)
			{
				Cast<ABullet>(Bullet)->TimeBeforeDestroy = 8.f;
				Bullet->SetActorRelativeScale3D(FVector(2.5f, 2.5f, 2.5f));
			}
			Bullet = GetWorld()->SpawnActor<ABullet>(BulletBlueprint, GetActorLocation(), FRotator(GetActorRotation().Pitch, GetActorRotation().Yaw + 20.f, GetActorRotation().Roll));
			if (Bullet)
			{
				Cast<ABullet>(Bullet)->TimeBeforeDestroy = 8.f;
				Bullet->SetActorRelativeScale3D(FVector(2.5f, 2.5f, 2.5f));
			}
			Bullet = GetWorld()->SpawnActor<ABullet>(BulletBlueprint, GetActorLocation(), FRotator(GetActorRotation().Pitch, GetActorRotation().Yaw - 20.f, GetActorRotation().Roll));
			if (Bullet)
			{
				Cast<ABullet>(Bullet)->TimeBeforeDestroy = 8.f;
				Bullet->SetActorRelativeScale3D(FVector(2.5f, 2.5f, 2.5f));
			}
			LastShot = 0.f;
		}
	}
	//Hvis boss er i nærangrep modus går han etter spilleren.
	if ((Mode == 2 || Mode == 4) && !Attack1)
	{
		if (NewDirection.Size() > AttackDistance)
		{
			Moving = true;
			FVector NewLocation = GetActorLocation() + GetActorForwardVector()*(speed * DeltaTime);
			SetActorLocation(NewLocation);
		}
		else
			Moving = false;
	}
	//Dreper fienden hvis han har falt utenfor kartet.
	if (GetActorLocation().Z < Cast<ATimGameMode>(GetWorld()->GetAuthGameMode())->KillZ)
	{
		ALastBoss::ImHit(100.f);
	}

	//Finner spillerens plassering og roterer etter den.
	if (!Dead)
	{
		NewDirection = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetActorLocation() - GetActorLocation();
		NewDirection.Z = 0.f;
		SetActorRotation(NewDirection.Rotation());
	}
}

void ALastBoss::ImHit(float Damage)
{
	//Fienden tar skade hvis den er truffet. Er han tom for liv blir han ødelagt.
	Health = Health - Damage;

	if (Health <= 0.f)
	{
		Dead = true;
	}
}


void ALastBoss::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor *OtherActor,
	UPrimitiveComponent *OtherComponent, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult &SweepResult)
{
	if (OtherActor->IsA(ATim::StaticClass()) && MeleeAttack)
	{
		if (Attack2)
		{
			if (Cast<ATim>(OtherActor)->GetMovementComponent()->IsFalling() == false)
				Cast<ATim>(OtherActor)->ImHit(1);
		}
		else
			Cast<ATim>(OtherActor)->ImHit(1);
		//Cast<ATim>(OtherActor)->ImHit(1);
	}
}

//Platformen skal bevege seg når bossen er dø og spilleren beveger seg på platformen. Dette gjør i blueprint via Finished.
void ALastBoss::OnPlatform(UPrimitiveComponent* OverlappedComponent, AActor *OtherActor,
	UPrimitiveComponent *OtherComponent, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult &SweepResult)
{
	if (OtherActor->IsA(ATim::StaticClass()))
	{
		if (Dead)
		{
			Finished = true;
			PlatformBox->DestroyComponent();
		}
	}
}
