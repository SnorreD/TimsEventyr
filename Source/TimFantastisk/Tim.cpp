// Fill out your copyright notice in the Description page of Project Settings.

#include "TimFantastisk.h"
#include "Tim.h"
#include "Bullet.h"
#include "Melee.h"
#include "Shield.h"
#include "TimGameMode.h"
#include "MySaveGame.h"
#include "Rope.h"


ATim::ATim()
{
	// Setter opp kameraet.
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->bAbsoluteRotation = true; // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->RelativeRotation = FRotator(-60.f, 0.f, 0.f);
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

										  // Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	//Setter opp muse sikte.
	CursorToWorld = CreateDefaultSubobject<UDecalComponent>("CursorToWorld");
	CursorToWorld->SetupAttachment(RootComponent);
	CursorToWorld->DecalSize = FVector(16.0f, 32.0f, 32.0f);
	CursorToWorld->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f).Quaternion());
}

void ATim::BeginPlay()
{
	Super::BeginPlay();

	if (GetWorld())
	{
		//Spilleren blir flyttet inn i en 'spiller-start'. Men jeg har ikke f�tt det til � funke med en variabel fra en lagrefil. S� hittil starter spilleren alltid p� Level1_1.
		auto CurrentGameMode = Cast<ATimGameMode>(GetWorld()->GetAuthGameMode());
		UMySaveGame* LoadGameInstance = Cast<UMySaveGame>(UGameplayStatics::CreateSaveGameObject(UMySaveGame::StaticClass()));
		LoadGameInstance = Cast<UMySaveGame>(UGameplayStatics::LoadGameFromSlot(LoadGameInstance->SaveSlotName, LoadGameInstance->UserIndex));

		if (Controller)
		{
			AActor *NewPawn = CurrentGameMode->FindPlayerStart(Controller, LoadGameInstance->Level);
			CurrentCheck = LoadGameInstance->Level;
			SetActorLocation(NewPawn->GetActorLocation());
			Controller->ClientSetRotation(NewPawn->GetActorRotation());
			Level = LoadGameInstance->Power;
		}

	}

}

void ATim::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Beveger mark�ren/musesikte.
	FHitResult Hit;
	bool HitResult = false;

	HitResult = GetWorld()->GetFirstPlayerController()->GetHitResultUnderCursorByChannel(UEngineTypes::ConvertToTraceType(ECC_WorldDynamic), true, Hit);

	if (HitResult)
	{
		FVector CursorFV = Hit.ImpactNormal;
		FRotator CursorR = CursorFV.Rotation();
		CursorToWorld->SetWorldLocation(Hit.Location);
		CursorToWorld->SetWorldRotation(CursorR);

		FVector CursorLocation = Hit.Location;
		UE_LOG(LogTemp, Warning, TEXT("Hit location %s!"), *Hit.Location.ToString());
		FVector TempLocation = FVector(CursorLocation.X, CursorLocation.Y, 30.f);

		FVector NewDirection = TempLocation - GetActorLocation();
		NewDirection.Z = 0.f;
		NewDirection.Normalize();
		SetActorRotation(NewDirection.Rotation());
	}
	else
	{
		GetCharacterMovement()->bOrientRotationToMovement = true;
		GetCharacterMovement()->RotationRate = FRotator(0.f, 10.f, 0.f);

	}

	//En sperre s� spilleren ikke kan angrepe med alt for korte mellomrom.
	if (Skytesperre == true)
	{
		TidSidenAngrep += DeltaTime;
		if (TidSidenAngrep > 0.37f)
		{
			if (RangeMelee == 1)
				RangeMelee = 0;
			if (TidSidenAngrep > AngrepMellomrom)
			{
				Skytesperre = false;
				TidSidenAngrep = 0.f;
				RangeMelee = 0;
			}
		}
	}

	//Dreper spilleren hvis han har falt utenfor kartet.
	FVector TimHvorErDu = GetActorLocation();
	if (TimHvorErDu.Z < Cast<ATimGameMode>(GetWorld()->GetAuthGameMode())->KillZ)
	{
		ATim::ImHit(3.f);
	}

	//Hvis Skjoldet er �delagt regenerer det sakte liv f�r det kan brukes igjen. Dette vises fint i HUD'en.
	if (ShieldDestruction == true)
	{
		ShieldDestroyed += DeltaTime;
		ShieldHealth = ShieldDestroyed * 0.5f;
		if (ShieldDestroyed > ShieldTimer)
		{
			ShieldHealth = 5.f;
			ShieldDestroyed = 0.f;
			ShieldDestruction = false;
		}
	}

	//Hvis spilleren har tatt skade er han immun en liten stund.
	if (DamageTaken == true)
	{
		TimeSinceDam += DeltaTime;
		if (TimeSinceDam > DamageInv)
		{
			DamageTaken = false;
			TimeSinceDam = 0.f;
		}
	}

	//Gj�r kulen som skal lades gradvis st�rre med tiden.
	if (Charge == true)
	{
		if (ChargeBullet)
		{

			Cast<ABullet>(ChargeBullet)->Damage += DeltaTime/2;
			ChargeBullet->SetActorRelativeScale3D(FVector(Cast<ABullet>(ChargeBullet)->Damage*2, Cast<ABullet>(ChargeBullet)->Damage*2, Cast<ABullet>(ChargeBullet)->Damage*2));
			if (Cast<ABullet>(ChargeBullet)->Damage >= 1.5f)
				Charge = false;

		}
	}

}

void ATim::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis("MoveX", this, &ATim::MoveX);
	InputComponent->BindAxis("MoveY", this, &ATim::MoveY);

	InputComponent->BindAction("Jump", IE_Pressed, this, &ATim::Jump);

	InputComponent->BindAction("AttackMelee", IE_Pressed, this, &ATim::AttackMelee);
	InputComponent->BindAction("AttackShoot", IE_Pressed, this, &ATim::AttackShoot);
	InputComponent->BindAction("AttackShoot", IE_Released, this, &ATim::AttackShootCharge);
	InputComponent->BindAction("Shield", IE_Pressed, this, &ATim::ShieldOn);
	InputComponent->BindAction("Shield", IE_Released, this, &ATim::ShieldOff);



}


void ATim::MoveX(float AxisValue)
{
	//G�r fremover. Hvis klatring beveger han klatreplatformen opp og ned.
	if (Climbing != true)
		AddMovementInput(FVector(1.f, 0.f, 0.f), AxisValue);
	else if (Climbing == true && AxisValue > 0)
		Cast<ARope>(Rope)->Velocity = 200.f;
	else if (Climbing == true && AxisValue < 0)
		Cast<ARope>(Rope)->Velocity = -200.f;
	else if (Climbing == true && AxisValue == 0)
		Cast<ARope>(Rope)->Velocity = 0.f;

}

void ATim::MoveY(float AxisValue)
{
	//G�r sidelengs.
	if (Climbing != true)
		AddMovementInput(FVector(0.f, 1.f, 0.f), AxisValue);
}

void ATim::Jump()
{
	//Hopp eller dobbelthopp hvis allerede hoppet. Funker bare en gang per hopp.
	if (Climbing == true)
		Climbing = false;

	if (CanJump())
	{
		ACharacter::Jump();
		if (DoubleJump)
			DoubleJump = false;
	}
	else if (!CanJump() && !DoubleJump)
	{
		LaunchCharacter(FVector(0.f, 0.f, 350.f), bool(false), bool(true));
		DoubleJump = true;
	}
}

void ATim::AttackMelee()
{
	//Hvis skytesperren ikke er p� kan spilleren lage et svert som f�lger med han i noen sekunder og tar skade av fiender/ �delegger kuler.
	if (Skytesperre != true)
	{
		if (ShieldOut == true)
		{
			Shield->Destroy();
			ShieldOut = false;
		}
		AActor *Sword = GetWorld()->SpawnActor<AMelee>(MeleeBlueprint, GetActorLocation() + GetActorForwardVector() * 100.f, FRotator(90.f, GetActorRotation().Yaw, GetActorRotation().Roll));
		Sword->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform, NAME_None);

		RangeMelee = 1;
		Skytesperre = true;
	}

}

void ATim::AttackShoot()
{
	//Hvis skytesperren ikke er p� kan spilleren skyte en kule som tar skade av fiender.
	if (Skytesperre != true)
	{
		if (ShieldOut == true)
		{
			Shield->Destroy();
			ShieldOut = false;
		}
		if (Level == 1)
		{
			AActor *Bullet = GetWorld()->SpawnActor<ABullet>(BulletBlueprint, GetActorLocation() + GetActorForwardVector() * 50.f, GetActorRotation());
			if (Bullet)
				Cast<ABullet>(Bullet)->EnemyBullet = false;

			RangeMelee = 2;
			Skytesperre = true;
		}
		else if (Level == 2 && !ChargeBullet)
		{
			ChargeBullet = GetWorld()->SpawnActor<ABullet>(BulletBlueprint, GetActorLocation() + GetActorForwardVector() * 100.f, GetActorRotation());
			if (ChargeBullet)
			{
				ChargeBullet->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform, NAME_None);
				Cast<ABullet>(ChargeBullet)->Speed = 0.f;
				Cast<ABullet>(ChargeBullet)->TimeBeforeDestroy = 100.f;
				Cast<ABullet>(ChargeBullet)->EnemyBullet = false;
				Charge = true;
				RangeMelee = 2;
				Skytesperre = true;
			}
			
		}
	}

}

	//Gj�r klar en kule for lading.
void ATim::AttackShootCharge()
{
	if (ChargeBullet)
	{
		ChargeBullet->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		Cast<ABullet>(ChargeBullet)->Speed = 700.f;
		Cast<ABullet>(ChargeBullet)->TimeLived = 0.f;
		Cast<ABullet>(ChargeBullet)->TimeBeforeDestroy = 3.f;
		ChargeBullet = nullptr;
		Charge = false;
	}
}

void ATim::ShieldOn()
{
	//Spilleren kan f� frem et skjold som bokker skade for en viss mengde liv f�r det m� regenereres.
	if (ShieldDestruction == false && Charge == false)
	{
		Shield = GetWorld()->SpawnActor<AShield>(ShieldBlueprint, GetActorLocation() + GetActorForwardVector() * 45.f, GetActorRotation());
		Shield->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform, NAME_None);
		Cast<AShield>(Shield)->Health = ShieldHealth;
		ShieldOut = true;
	}
}

//N�r spilleren slipper skjold tasten forsvinner skjoldet.
void ATim::ShieldOff()
{
	if (Shield)
	{
		Shield->Destroy();
		ShieldOut = false;
		if (ShieldHealth <= 0.f)
			ShieldDestruction = true;
		
	}
}


//Hvis spilleren g�r tom for liv lades kartet p� nytt og alt g�r tilbake.
void ATim::ImHit(float Damage)
{
	if (!DamageTaken)
	{
		Health -= Damage;

		DamageTaken = true;
	}

	if (Health <= 0)
	{
		if (Shield)
			Shield->Destroy();

		UMySaveGame* LoadGameInstance = Cast<UMySaveGame>(UGameplayStatics::CreateSaveGameObject(UMySaveGame::StaticClass()));
		LoadGameInstance = Cast<UMySaveGame>(UGameplayStatics::LoadGameFromSlot(LoadGameInstance->SaveSlotName, LoadGameInstance->UserIndex));

		UGameplayStatics::OpenLevel(this, LoadGameInstance->Map);
	}
	
}