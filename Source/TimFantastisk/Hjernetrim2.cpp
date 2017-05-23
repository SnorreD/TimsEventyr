// Fill out your copyright notice in the Description page of Project Settings.

#include "TimFantastisk.h"
#include "Hjernetrim2.h"
#include "Tim.h"
#include "TimGameMode.h"
#include "Hjernetrim2Fiende.h"


// Sets default values
AHjernetrim2::AHjernetrim2()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Initialiserer alle elementer i gåten.
		//Annet:
	Entrance = CreateDefaultSubobject<UBoxComponent>(TEXT("Entrance"));
	Entrance->bGenerateOverlapEvents = true;
	Entrance->OnComponentBeginOverlap.AddDynamic(this, &AHjernetrim2::OnOverlapEntrance);
	RootComponent = Entrance;

	Key1 = CreateDefaultSubobject<UBoxComponent>(TEXT("Key1"));
	Key1->bGenerateOverlapEvents = true;
	Key1->OnComponentBeginOverlap.AddDynamic(this, &AHjernetrim2::OnOverlapKey1);
	Key1->SetupAttachment(RootComponent);

	Key2 = CreateDefaultSubobject<UBoxComponent>(TEXT("Key2"));
	Key2->bGenerateOverlapEvents = true;
	Key2->OnComponentBeginOverlap.AddDynamic(this, &AHjernetrim2::OnOverlapKey2);
	Key2->SetupAttachment(RootComponent);

	Key1Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Key1Mesh"));
	Key1Mesh->SetupAttachment(Key1);

	Key2Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Key2Mesh"));
	Key2Mesh->SetupAttachment(Key2);

	Alter = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Alter"));
	Alter->SetupAttachment(Key2);

	Platform = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Platform"));
	Platform->SetupAttachment(RootComponent);

	Wait = CreateDefaultSubobject<UBoxComponent>(TEXT("Wait"));
	Wait->SetupAttachment(RootComponent);

	Door = CreateDefaultSubobject<UBoxComponent>(TEXT("Door"));
	Door->bGenerateOverlapEvents = true;
	Door->OnComponentBeginOverlap.AddDynamic(this, &AHjernetrim2::OnOverlapDoor);
	Door->SetupAttachment(RootComponent);

	Spawn1 = CreateDefaultSubobject<UBoxComponent>(TEXT("Spawn1"));
	Spawn1->SetupAttachment(RootComponent);
	Spawn2 = CreateDefaultSubobject<UBoxComponent>(TEXT("Spawn2"));
	Spawn2->SetupAttachment(RootComponent);
	Spawn3 = CreateDefaultSubobject<UBoxComponent>(TEXT("Spawn3"));
	Spawn3->SetupAttachment(RootComponent);
	Spawn4 = CreateDefaultSubobject<UBoxComponent>(TEXT("Spawn4"));
	Spawn4->SetupAttachment(RootComponent);

		//Konteinere:
	BlueContainer = CreateDefaultSubobject<UBoxComponent>(TEXT("BlueContainer"));
	BlueContainer->bGenerateOverlapEvents = true;
	BlueContainer->OnComponentBeginOverlap.AddDynamic(this, &AHjernetrim2::OnOverlapBlueCo);
	BlueContainer->SetupAttachment(RootComponent);

	GreenContainer = CreateDefaultSubobject<UBoxComponent>(TEXT("GreenContainer"));
	GreenContainer->bGenerateOverlapEvents = true;
	GreenContainer->OnComponentBeginOverlap.AddDynamic(this, &AHjernetrim2::OnOverlapGreenCo);
	GreenContainer->SetupAttachment(RootComponent);

	PinkContainer = CreateDefaultSubobject<UBoxComponent>(TEXT("PinkContainer"));
	PinkContainer->bGenerateOverlapEvents = true;
	PinkContainer->OnComponentBeginOverlap.AddDynamic(this, &AHjernetrim2::OnOverlapPinkCo);
	PinkContainer->SetupAttachment(RootComponent);

	RedContainer = CreateDefaultSubobject<UBoxComponent>(TEXT("RedContainer"));
	RedContainer->bGenerateOverlapEvents = true;
	RedContainer->OnComponentBeginOverlap.AddDynamic(this, &AHjernetrim2::OnOverlapRedCo);
	RedContainer->SetupAttachment(RootComponent);

		//Krystaller:
	BlueCrystal = CreateDefaultSubobject<UBoxComponent>(TEXT("BlueCrystal"));
	BlueCrystal->bGenerateOverlapEvents = true;
	BlueCrystal->OnComponentBeginOverlap.AddDynamic(this, &AHjernetrim2::OnOverlapBlueCr);
	BlueCrystal->SetupAttachment(RootComponent);
	BlueCrystalMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BlueMesh"));
	BlueCrystalMesh->SetupAttachment(BlueCrystal);

	GreenCrystal = CreateDefaultSubobject<UBoxComponent>(TEXT("GreenCrystal"));
	GreenCrystal->bGenerateOverlapEvents = true;
	GreenCrystal->OnComponentBeginOverlap.AddDynamic(this, &AHjernetrim2::OnOverlapGreenCr);
	GreenCrystal->SetupAttachment(RootComponent);
	GreenCrystalMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GreenMesh"));
	GreenCrystalMesh->SetupAttachment(GreenCrystal);

	PinkCrystal = CreateDefaultSubobject<UBoxComponent>(TEXT("PinkCrystal"));
	PinkCrystal->bGenerateOverlapEvents = true;
	PinkCrystal->OnComponentBeginOverlap.AddDynamic(this, &AHjernetrim2::OnOverlapPinkCr);
	PinkCrystal->SetupAttachment(RootComponent);
	PinkCrystalMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PinkMesh"));
	PinkCrystalMesh->SetupAttachment(PinkCrystal);

	RedCrystal = CreateDefaultSubobject<UBoxComponent>(TEXT("RedCrystal"));
	RedCrystal->bGenerateOverlapEvents = true;
	RedCrystal->OnComponentBeginOverlap.AddDynamic(this, &AHjernetrim2::OnOverlapRedCr);
	RedCrystal->SetupAttachment(RootComponent);
	RedCrystalMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RedMesh"));
	RedCrystalMesh->SetupAttachment(RedCrystal);

	//Setter alle krystaller og kontainere til falsk.
	for (int i = 0; i < 4; i++)
	{
		Crystals[i] = false;
		Container[i] = false;
	}
		

}

// Called when the game starts or when spawned
void AHjernetrim2::BeginPlay()
{
	Super::BeginPlay();

	Key2Pos = Key2->GetComponentLocation();
	PlatPos = Platform->GetComponentLocation();
	
}

// Called every frame
void AHjernetrim2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Message)
	{
		Timer += DeltaTime;
		auto CurrentGameMode = Cast<ATimGameMode>(GetWorld()->GetAuthGameMode());
		CurrentGameMode->Tips = "Du trenger " + MessageText;
		if (Timer > Time)
		{
			CurrentGameMode->Tips = "";
			Timer = 0.f;
			Message = false;
		}
	}
	if (ContainerOn && (Working == -1 || Working == ContainerNum))
	{
		Timer += DeltaTime;
		Crystals[ContainerNum] = false;
		Working = ContainerNum;
		if (Timer < Time)
		{
			switch (ContainerNum)
			{
			case 0:
				BlueContainer->SetWorldLocation(FVector(ContainerPos.X, ContainerPos.Y, ContainerPos.Z - (Timer*75.f)));
				break;
			case 1:
				GreenContainer->SetWorldLocation(FVector(ContainerPos.X, ContainerPos.Y, ContainerPos.Z - (Timer*75.f)));
				break;
			case 2:
				PinkContainer->SetWorldLocation(FVector(ContainerPos.X, ContainerPos.Y, ContainerPos.Z - (Timer*75.f)));
				break;
			case 3:
				RedContainer->SetWorldLocation(FVector(ContainerPos.X, ContainerPos.Y, ContainerPos.Z - (Timer*75.f)));
				break;
			}
		}

		else
		{
			ContainerOn = false;
			Timer = 0;
			Working = -1;
		}
	}

	if (Container[0] && Container[1] && Container[2] && Container[3] && Working == -1)
	{
		Timer += DeltaTime;
		if (Timer < Time)
			Key2->SetWorldLocation(FVector(Key2Pos.X, Key2Pos.Y, Key2Pos.Z + (Timer*46.f)));
		else
		{
			Working = 5;
			Timer = 0;
		}
	}

	if (Working == 6)
	{
		Timer += DeltaTime;
		if (Timer > WaitTime / 2 && Wait)
			Wait->DestroyComponent();
		if (Timer > WaitTime)
		{
			APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
			Cast<ATim>(MyPlayer)->EnableInput(PlayerController);
			USpringArmComponent *Camera = Cast<ATim>(MyPlayer)->CameraBoom;
			Camera->TargetArmLength = 800.f;
			Camera->RelativeRotation = FRotator(-60.f, 0.f, 0.f);
			Camera->TargetOffset = FVector(0.f, 0.f, 0.f);
			Working = -1.f;
		}
	}

	if (Working == 7)
	{
		Timer += DeltaTime;
		if (Timer < Time)
			Platform->SetWorldLocation(FVector(PlatPos.X, PlatPos.Y, PlatPos.Z + (Timer*110.f)));
		else
		{
			Timer = 0.f;
			Working = -1;
		}
	}
		
}

//Konteiner kollisjons-handlinger.
void AHjernetrim2::OnOverlapBlueCo(UPrimitiveComponent* OverlappedComponent, AActor *OtherActor,
	UPrimitiveComponent *OtherComponent, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult &SweepResult)
{
	if (OtherActor->IsA(ATim::StaticClass()))
	{
		OverlapContainer(0);
	}
}
void AHjernetrim2::OnOverlapGreenCo(UPrimitiveComponent* OverlappedComponent, AActor *OtherActor,
	UPrimitiveComponent *OtherComponent, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult &SweepResult)
{
	if (OtherActor->IsA(ATim::StaticClass()))
	{
		OverlapContainer(1);
	}
}
void AHjernetrim2::OnOverlapPinkCo(UPrimitiveComponent* OverlappedComponent, AActor *OtherActor,
	UPrimitiveComponent *OtherComponent, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult &SweepResult)
{
	if (OtherActor->IsA(ATim::StaticClass()))
	{
		OverlapContainer(2);
	}
}
void AHjernetrim2::OnOverlapRedCo(UPrimitiveComponent* OverlappedComponent, AActor *OtherActor,
	UPrimitiveComponent *OtherComponent, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult &SweepResult)
{
	if (OtherActor->IsA(ATim::StaticClass()))
	{
		OverlapContainer(3);
	}
}
//Krystall kollisjons-handlinger:
void AHjernetrim2::OnOverlapBlueCr(UPrimitiveComponent* OverlappedComponent, AActor *OtherActor,
	UPrimitiveComponent *OtherComponent, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult &SweepResult)
{
	if (OtherActor->IsA(ATim::StaticClass()))
	{
		Crystals[0] = true;
		BlueCrystalMesh->DestroyComponent();
		BlueCrystal->DestroyComponent();
	}
	else if (OtherActor->IsA(AHjernetrim2Fiende::StaticClass()) && !Taken[0])
	{
		BlueCrystal->SetWorldLocation(FVector(OtherActor->GetActorLocation().X, OtherActor->GetActorLocation().Y, OtherActor->GetActorLocation().Z + 100.f));
		BlueCrystal->AttachToComponent(Cast<AHjernetrim2Fiende>(OtherActor)->RootCapsule, FAttachmentTransformRules::KeepWorldTransform, NAME_None);
		Cast<AHjernetrim2Fiende>(OtherActor)->TurnDegree = 180.f;
		Cast<AHjernetrim2Fiende>(OtherActor)->StartTurn = true;
		Taken[0] = true;
	}
}
void AHjernetrim2::OnOverlapGreenCr(UPrimitiveComponent* OverlappedComponent, AActor *OtherActor,
	UPrimitiveComponent *OtherComponent, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult &SweepResult)
{
	if (OtherActor->IsA(ATim::StaticClass()))
	{
		Crystals[1] = true;
		GreenCrystalMesh->DestroyComponent();
		GreenCrystal->DestroyComponent();
	}
	else if (OtherActor->IsA(AHjernetrim2Fiende::StaticClass()) && !Taken[1])
	{
		GreenCrystal->SetWorldLocation(FVector(OtherActor->GetActorLocation().X, OtherActor->GetActorLocation().Y, OtherActor->GetActorLocation().Z + 100.f));
		GreenCrystal->AttachToComponent(Cast<AHjernetrim2Fiende>(OtherActor)->RootCapsule, FAttachmentTransformRules::KeepWorldTransform, NAME_None);
		Cast<AHjernetrim2Fiende>(OtherActor)->TurnDegree = 90.f;
		Cast<AHjernetrim2Fiende>(OtherActor)->StartTurn = true;
		Taken[1] = true;
	}
}
void AHjernetrim2::OnOverlapPinkCr(UPrimitiveComponent* OverlappedComponent, AActor *OtherActor,
	UPrimitiveComponent *OtherComponent, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult &SweepResult)
{
	if (OtherActor->IsA(ATim::StaticClass()))
	{
		Crystals[2] = true;
		PinkCrystalMesh->DestroyComponent();
		PinkCrystal->DestroyComponent();
	}
	else if (OtherActor->IsA(AHjernetrim2Fiende::StaticClass()) && !Taken[2])
	{
		PinkCrystal->SetWorldLocation(FVector(OtherActor->GetActorLocation().X, OtherActor->GetActorLocation().Y, OtherActor->GetActorLocation().Z + 100.f));
		PinkCrystal->AttachToComponent(Cast<AHjernetrim2Fiende>(OtherActor)->RootCapsule, FAttachmentTransformRules::KeepWorldTransform, NAME_None);
		Cast<AHjernetrim2Fiende>(OtherActor)->TurnDegree = -90.f;
		Cast<AHjernetrim2Fiende>(OtherActor)->StartTurn = true;
		Taken[2] = true;
	}
}
void AHjernetrim2::OnOverlapRedCr(UPrimitiveComponent* OverlappedComponent, AActor *OtherActor,
	UPrimitiveComponent *OtherComponent, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult &SweepResult)
{
	if (OtherActor->IsA(ATim::StaticClass()))
	{
		Crystals[3] = true;
		if (RedCrystalMesh)
			RedCrystalMesh->DestroyComponent();
		if (RedCrystal)
			RedCrystal->DestroyComponent();
	}
	else if (OtherActor->IsA(AHjernetrim2Fiende::StaticClass()) && !Taken[3])
	{
		RedCrystal->SetWorldLocation(FVector(OtherActor->GetActorLocation().X, OtherActor->GetActorLocation().Y, OtherActor->GetActorLocation().Z + 100.f));
		RedCrystal->AttachToComponent(Cast<AHjernetrim2Fiende>(OtherActor)->RootCapsule, FAttachmentTransformRules::KeepWorldTransform, NAME_None);
		Cast<AHjernetrim2Fiende>(OtherActor)->TurnDegree = 180.f;
		Cast<AHjernetrim2Fiende>(OtherActor)->StartTurn = true;
		Taken[3] = true;
	}
}

void AHjernetrim2::OnOverlapKey1(UPrimitiveComponent* OverlappedComponent, AActor *OtherActor,
	UPrimitiveComponent *OtherComponent, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult &SweepResult)
{
	if (OtherActor->IsA(ATim::StaticClass()))
	{
		Keys--;
		Working = 7;
		Key1Mesh->DestroyComponent();
		Key1->DestroyComponent();
	}
}
void AHjernetrim2::OnOverlapKey2(UPrimitiveComponent* OverlappedComponent, AActor *OtherActor,
	UPrimitiveComponent *OtherComponent, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult &SweepResult)
{
	if (OtherActor->IsA(ATim::StaticClass()))
	{
		Keys--;
		Key2Mesh->DestroyComponent();
		Key2->DestroyComponent();
	}
}
void AHjernetrim2::OnOverlapEntrance(UPrimitiveComponent* OverlappedComponent, AActor *OtherActor,
	UPrimitiveComponent *OtherComponent, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult &SweepResult)
{
	if (OtherActor->IsA(ATim::StaticClass()))
	{
		MyPlayer = OtherActor;
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
		Cast<ATim>(OtherActor)->DisableInput(PlayerController);
		USpringArmComponent *Camera = Cast<ATim>(OtherActor)->CameraBoom;
		Camera->TargetArmLength = 1400.f;
		Camera->RelativeRotation = FRotator(-45.f, 90.f, 0.f);
		Camera->TargetOffset = FVector(0.f, 600.f, 0.f);
		AActor *Fiende = GetWorld()->SpawnActor<AHjernetrim2Fiende>(FiendeBlueprint, Spawn1->GetComponentLocation(), Spawn1->GetComponentRotation());
		if (Fiende)
			Cast<AHjernetrim2Fiende>(Fiende)->SetAttackMode(2);
		Fiende = GetWorld()->SpawnActor<AHjernetrim2Fiende>(FiendeBlueprint, Spawn2->GetComponentLocation(), Spawn2->GetComponentRotation());
		if (Fiende)
			Cast<AHjernetrim2Fiende>(Fiende)->SetAttackMode(1);
		Fiende = GetWorld()->SpawnActor<AHjernetrim2Fiende>(FiendeBlueprint, Spawn3->GetComponentLocation(), Spawn3->GetComponentRotation());
		if (Fiende)
			Cast<AHjernetrim2Fiende>(Fiende)->SetAttackMode(3);
		Fiende = GetWorld()->SpawnActor<AHjernetrim2Fiende>(FiendeBlueprint, Spawn4->GetComponentLocation(), Spawn4->GetComponentRotation());
		if (Fiende)
			Cast<AHjernetrim2Fiende>(Fiende)->SetAttackMode(4);
		Working = 6;
		Entrance->DestroyComponent();
	}
}
void AHjernetrim2::OnOverlapDoor(UPrimitiveComponent* OverlappedComponent, AActor *OtherActor,
	UPrimitiveComponent *OtherComponent, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult &SweepResult)
{
	if (OtherActor->IsA(ATim::StaticClass()))
	{
		if (Keys != 0)
		{
			Message = true;
			MessageText = FString::FromInt(Keys) + KeyText;
		}
		else
		{
			Finished = true;
			Door->DestroyComponent();
		}
	}
}


void AHjernetrim2::OverlapContainer(int tall)
{
	if (Crystals[tall] && !Container[tall] && Working == -1)
	{
		ContainerOn = true;
		ContainerNum = tall;
		Container[tall] = true;
		Timer = 0;
		switch (tall)
		{
		case 0:
			ContainerPos = BlueContainer->GetComponentLocation();
			break;
		case 1:
			ContainerPos = GreenContainer->GetComponentLocation();
			break;
		case 2:
			ContainerPos = PinkContainer->GetComponentLocation();
			break;
		case 3:
			ContainerPos = RedContainer->GetComponentLocation();
			break;
		}
	}
	else if (!Container[tall] && Working == -1)
	{
		Message = true;
		switch (tall)
		{
		case 0:
			MessageText = Blue;
			break;
		case 1:
			MessageText = Green;
			break;
		case 2:
			MessageText = Pink;
			break;
		case 3:
			MessageText = Red;
			break;
		}
		Timer = 0;
	}
}