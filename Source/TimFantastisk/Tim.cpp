// Fill out your copyright notice in the Description page of Project Settings.

#include "TimFantastisk.h"
#include "Tim.h"
#include "Bullet.h"
#include "Melee.h"
#include "Shield.h"
#include "TimGameMode.h"
#include "MySaveGame.h"


ATim::ATim()
{
	OurVisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OurVisibleComponent"));

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

	OurVisibleComponent->SetupAttachment(RootComponent);

	//Setter opp muse sikte.
	CursorToWorld = CreateDefaultSubobject<UDecalComponent>("CursorToWorld");
	CursorToWorld->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UMaterial> DecalMaterialAsset(TEXT("Game/Assets/M_Cursor_Decal"));
	if (DecalMaterialAsset.Succeeded())
	{
		CursorToWorld->SetDecalMaterial(DecalMaterialAsset.Object);
	}
	CursorToWorld->DecalSize = FVector(16.0f, 32.0f, 32.0f);
	CursorToWorld->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f).Quaternion());
}

void ATim::BeginPlay()
{
	Super::BeginPlay();

	if (GetWorld())
	{
		//Spilleren blir flyttet inn i en 'spiller-start'. Men jeg har ikke fått det til å funke med en variabel fra en lagrefil. Så hittil starter spilleren alltid på Level1_1.
		auto CurrentGameMode = Cast<ATimGameMode>(GetWorld()->GetAuthGameMode());
		UMySaveGame* LoadGameInstance = Cast<UMySaveGame>(UGameplayStatics::CreateSaveGameObject(UMySaveGame::StaticClass()));
		LoadGameInstance = Cast<UMySaveGame>(UGameplayStatics::LoadGameFromSlot(LoadGameInstance->SaveSlotName, LoadGameInstance->UserIndex));

		if (Controller)
		{
			AActor *NewPawn = CurrentGameMode->FindPlayerStart(Controller, /*LoadGameInstance->Level*/ "Level1_1");
			SetActorLocation(NewPawn->GetActorLocation());
			Controller->ClientSetRotation(NewPawn->GetActorRotation());
		}
	}
	

}

void ATim::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Beveger markøren/musesikte.
	FHitResult Hit;
	bool HitResult = false;

	HitResult = GetWorld()->GetFirstPlayerController()->GetHitResultUnderCursorByChannel(UEngineTypes::ConvertToTraceType(ECC_WorldStatic), true, Hit);

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

	//En sperre så spilleren ikke kan angrepe med alt for korte mellomrom.
	if (Skytesperre == true)
	{
		TidSidenAngrep += DeltaTime;
		if (TidSidenAngrep > AngrepMellomrom)
		{
			Skytesperre = false;
			TidSidenAngrep = 0.f;
		}
	}

	//Dreper spilleren hvis han har falt utenfor kartet.
	FVector TimHvorErDu = GetActorLocation();
	if (TimHvorErDu.Z < Cast<ATimGameMode>(GetWorld()->GetAuthGameMode())->KillZ)
	{
		ATim::ImHit(3.f);
	}

	//Hvis Skjoldet er ødelagt regenerer det sakte liv før det kan brukes igjen. Dette vises fint i HUD'en.
	if (ShieldDestruction == true)
	{
		ShieldDestroyed += DeltaTime;
		ShieldHealth = ShieldDestroyed * 0.5f;
		if (ShieldDestroyed > ShieldTimer)
		{
			ShieldHealth = 10.f;
			ShieldDestroyed = 0.f;
			ShieldDestruction = false;
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
	InputComponent->BindAction("Shield", IE_Pressed, this, &ATim::ShieldOn);
	InputComponent->BindAction("Shield", IE_Released, this, &ATim::ShieldOff);



}


void ATim::MoveX(float AxisValue)
{
	//Går fremover.
	AddMovementInput(FVector(1.f, 0.f, 0.f), AxisValue);

}

void ATim::MoveY(float AxisValue)
{
	//Går sidelengs.
	AddMovementInput(FVector(0.f, 1.f, 0.f), AxisValue);

}

void ATim::Jump()
{
	//Hopp
	ACharacter::Jump();
}

void ATim::AttackMelee()
{
	//Hvis skytesperren ikke er på kan spilleren lage et svert som følger med han i noen sekunder og tar skade av fiender/ ødelegger kuler.
	if (Skytesperre != true)
	{
		if (ShieldOut == true)
		{
			Shield->Destroy();
			ShieldOut = false;
		}
		AActor *Sword = GetWorld()->SpawnActor<AMelee>(MeleeBlueprint, GetActorLocation() + GetActorForwardVector() * 100.f, FRotator(90.f, GetActorRotation().Yaw, GetActorRotation().Roll));
		Sword->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform, NAME_None);

		Skytesperre = true;
	}

}

void ATim::AttackShoot()
{
	//Hvis skytesperren ikke er på kan spilleren skyte en kule som tar skade av fiender.
	if (Skytesperre != true)
	{
		if (ShieldOut == true)
		{
			Shield->Destroy();
			ShieldOut = false;
		}
		AActor *Bullet = GetWorld()->SpawnActor<ABullet>(BulletBlueprint, GetActorLocation() + GetActorForwardVector() * 100.f, GetActorRotation());
		if (Bullet)
			Cast<ABullet>(Bullet)->EnemyBullet = false;

		Skytesperre = true;
	}

}

void ATim::ShieldOn()
{
	//Spilleren kan få frem et skjold som bokker skade for en viss mengde liv før det må regenereres.
	if (ShieldDestruction == false)
	{
		Shield = GetWorld()->SpawnActor<AShield>(ShieldBlueprint, GetActorLocation() + GetActorForwardVector() * 100.f, GetActorRotation());
		Shield->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform, NAME_None);
		Cast<AShield>(Shield)->Health = ShieldHealth;
		ShieldOut = true;
	}
}

//Når spilleren slipper skjold tasten forsvinner skjoldet.
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


//Hvis spilleren går tom for liv lades kartet på nytt og alt går tilbake.
void ATim::ImHit(float Damage)
{
	Health -= Damage;
	if (Health <= 0)
	{
		if (Shield)
			Shield->Destroy();

		UMySaveGame* LoadGameInstance = Cast<UMySaveGame>(UGameplayStatics::CreateSaveGameObject(UMySaveGame::StaticClass()));
		LoadGameInstance = Cast<UMySaveGame>(UGameplayStatics::LoadGameFromSlot(LoadGameInstance->SaveSlotName, LoadGameInstance->UserIndex));

		UGameplayStatics::OpenLevel(this, LoadGameInstance->Map);
	}
}