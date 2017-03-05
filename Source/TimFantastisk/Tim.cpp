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

	// Don't rotate character to camera direction
	//bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	//bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 90.f, 0.f);
	//GetCharacterMovement()->bConstrainToPlane = true;
	//GetCharacterMovement()->bSnapToPlaneAtStart = true;
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
}

// Called to bind functionality to input
void ATim::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis("MoveX", this, &ATim::MoveX);
	InputComponent->BindAxis("MoveY", this, &ATim::MoveY);
	InputComponent->BindAction("Jump", IE_Pressed, this, &ATim::Jump);
	InputComponent->BindAction("AttackUp", IE_Pressed, this, &ATim::AttackUp);
	InputComponent->BindAction("AttackDown", IE_Pressed, this, &ATim::AttackDown);
	InputComponent->BindAction("AttackLeft", IE_Pressed, this, &ATim::AttackLeft);
	InputComponent->BindAction("AttackRight", IE_Pressed, this, &ATim::AttackRight);

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

void ATim::AttackUp()
{
	GetWorld()->SpawnActor<ABullet>(BulletBlueprint, GetActorLocation() + GetActorForwardVector() * 100.f, FRotator( 0.f, 0.f, 0.f));
}

void ATim::AttackDown()
{
	GetWorld()->SpawnActor<ABullet>(BulletBlueprint, GetActorLocation() + GetActorForwardVector() * -100.f, FRotator(0.f, 180.f, 0.f));
}

void ATim::AttackLeft()
{
	GetWorld()->SpawnActor<ABullet>(BulletBlueprint, GetActorLocation() + GetActorRightVector() * -100.f, FRotator(0.f, -90.f, 0.f));
}

void ATim::AttackRight()
{
	GetWorld()->SpawnActor<ABullet>(BulletBlueprint, GetActorLocation() + GetActorRightVector() * 100.f, FRotator(0.f, 90.f, 0.f));
}