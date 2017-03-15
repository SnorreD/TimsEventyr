// Fill out your copyright notice in the Description page of Project Settings.

#include "TimFantastisk.h"
#include "Tim.h"
#include "Bullet.h"
#include "Melee.h"


// Sets default values
ATim::ATim()
{
	// Create a camera and a visible object
	OurVisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OurVisibleComponent"));

	// Create a camera boom...
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

	// Don't rotate character to camera direction
	//bUseControllerRotationPitch = false;
	//bUseControllerRotationYaw = false;
	//bUseControllerRotationRoll = false;

	// Configure character movement
	//GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	//GetCharacterMovement()->RotationRate = FRotator(0.f, 690.f, 0.f);
	//GetCharacterMovement()->bConstrainToPlane = true;
	//GetCharacterMovement()->bSnapToPlaneAtStart = true;

	//Create a decal in the world to show the cursor's location
	CursorToWorld = CreateDefaultSubobject<UDecalComponent>("CursorToWorld");
	CursorToWorld->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UMaterial> DecalMaterialAsset(TEXT("Content'/Assets/M_Cursor_Decal'"));
	if (DecalMaterialAsset.Succeeded())
	{
		CursorToWorld->SetDecalMaterial(DecalMaterialAsset.Object);
	}
	CursorToWorld->DecalSize = FVector(16.0f, 32.0f, 32.0f);
	CursorToWorld->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f).Quaternion());
	//APlayerController* MyController = GetWorld()->GetFirstPlayerController();
		//MyController->bShowMouseCursor = true;


	// Activate ticking in order to update the cursor every frame.
	//PrimaryActorTick.bCanEverTick = true;
	//PrimaryActorTick.bStartWithTickEnabled = true;
}

// Called when the game starts or when spawned
void ATim::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ATim::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	/// Move the cursor
	FHitResult Hit;
	bool HitResult = false;

	HitResult = GetWorld()->GetFirstPlayerController()->GetHitResultUnderCursorByChannel(UEngineTypes::ConvertToTraceType(ECC_WorldStatic), true, Hit);

	if (HitResult)
	{
		FVector CursorFV = Hit.ImpactNormal;
		FRotator CursorR = CursorFV.Rotation();
		CursorToWorld->SetWorldLocation(Hit.Location);
		CursorToWorld->SetWorldRotation(CursorR);

		///Set the new direction of the pawn:
		FVector CursorLocation = Hit.Location;
		UE_LOG(LogTemp, Warning, TEXT("Hit location %s!"), *Hit.Location.ToString());
		FVector TempLocation = FVector(CursorLocation.X, CursorLocation.Y, 30.f);

		FVector NewDirection = TempLocation - GetActorLocation();
		NewDirection.Z = 0.f;
		NewDirection.Normalize();
		SetActorRotation(NewDirection.Rotation());
	}

	if (Skytesperre == true)
	{
		TidSidenAngrep += DeltaTime;
		if (TidSidenAngrep > AngrepMellomrom)
		{
			Skytesperre = false;
			TidSidenAngrep = 0.f;
		}
	}

	FVector TimHvorErDu = GetActorLocation();
	if (TimHvorErDu.Z < -900.f)
	{
		UGameplayStatics::OpenLevel(GetWorld(), "Prototype_Map");
	}

}

// Called to bind functionality to input
void ATim::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis("MoveX", this, &ATim::MoveX);
	InputComponent->BindAxis("MoveY", this, &ATim::MoveY);

	InputComponent->BindAction("Jump", IE_Pressed, this, &ATim::Jump);

	InputComponent->BindAction("Attack", IE_Pressed, this, &ATim::Attack);

	InputComponent->BindAction("Mode1", IE_Pressed, this, &ATim::Modus1);
	InputComponent->BindAction("Mode2", IE_Pressed, this, &ATim::Modus2);
	InputComponent->BindAction("Mode3", IE_Pressed, this, &ATim::Modus3);



}


void ATim::MoveX(float AxisValue)
{

	AddMovementInput(FVector(1.f, 0.f, 0.f), AxisValue);

}

void ATim::MoveY(float AxisValue)
{

	AddMovementInput(FVector(0.f, 1.f, 0.f), AxisValue);

}

void ATim::Jump()
{
	ACharacter::Jump();
}

void ATim::Attack()
{
	
	if (Skytesperre != true)
	{
		if (Mode == 1)
			GetWorld()->SpawnActor<AMelee>(MeleeBlueprint, GetActorLocation() + GetActorForwardVector() * 100.f, FRotator(90.f, GetActorRotation().Yaw, GetActorRotation().Roll));
		if (Mode == 2)
			GetWorld()->SpawnActor<ABullet>(BulletBlueprint, GetActorLocation() + GetActorForwardVector() * 100.f, GetActorRotation());

		Skytesperre = true;
	}
}


void ATim::Modus1()
{
	Mode = 1;
}

void ATim::Modus2()
{
	Mode = 2;
}

void ATim::Modus3()
{
	Mode = 3;
}

void ATim::ImHit()
{
	UGameplayStatics::OpenLevel(GetWorld(), "Prototype_Map");
}