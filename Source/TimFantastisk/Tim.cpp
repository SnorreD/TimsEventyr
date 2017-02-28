// Fill out your copyright notice in the Description page of Project Settings.

#include "TimFantastisk.h"
#include "Tim.h"
#include "Bullet.h"


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

	CursorToWorld = CreateDefaultSubobject<UDecalComponent>("CursorToWorld");
	CursorToWorld->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UMaterial> DecalMaterialAsset(TEXT("Assets'/Game/Assets/M_Cursor_Decal.M_Cursor_Decal'"));
	if (DecalMaterialAsset.Succeeded())
	{
		CursorToWorld->SetDecalMaterial(DecalMaterialAsset.Object);
	}
	CursorToWorld->DecalSize = FVector(16.0f, 32.0f, 32.0f);
	CursorToWorld->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f).Quaternion());
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

	bool HitResult = false;

	FHitResult Hit;
	HitResult = GetWorld()->GetFirstPlayerController()->GetHitResultUnderCursorByChannel(UEngineTypes::ConvertToTraceType(ECC_WorldStatic), true, Hit);

	if (HitResult)
	{
		FVector CursorFV = Hit.ImpactNormal;
		FRotator CursorR = CursorFV.Rotation();
		CursorToWorld->SetWorldLocation(Hit.Location);
		CursorToWorld->SetWorldRotation(CursorR);


		FVector CursorLocation = Hit.Location;
		UE_LOG(LogTemp, Warning, TEXT("Cursor location %s!"), *CursorLocation.ToString());
		FVector TempLocation = FVector(CursorLocation.X, CursorLocation.Y, 30.f);
		//        if (CursorMesh)
		//            CursorMesh->SetWorldLocation(TempLocation);
		//        else
		//            UE_LOG(LogTemp, Warning, TEXT("Cursor Mesh not found"));

		FVector NewDirection = TempLocation - GetActorLocation();
		NewDirection.Z = 0.f;
		NewDirection.Normalize();
		SetActorRotation(NewDirection.Rotation());
	}

}

// Called to bind functionality to input
void ATim::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis("MoveX", this, &ATim::MoveX);
	InputComponent->BindAxis("MoveY", this, &ATim::MoveY);
	InputComponent->BindAction("Jump", IE_Pressed, this, &ATim::Jump);
	InputComponent->BindAction("Shoot", IE_Pressed, this, &ATim::Shoot);

}


void ATim::MoveX(float AxisValue)
{

	AddMovementInput(GetActorForwardVector(), AxisValue);

}

void ATim::MoveY(float AxisValue)
{

	AddMovementInput(GetActorRightVector(), AxisValue);

}

void ATim::Jump()
{
	ACharacter::Jump();
}

void ATim::Shoot()
{
	GetWorld()->SpawnActor<ABullet>(BulletBlueprint, GetActorLocation() + GetActorForwardVector() * 100.f,
		GetActorRotation());
}