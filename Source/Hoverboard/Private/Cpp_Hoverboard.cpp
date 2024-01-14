// Fill out your copyright notice in the Description page of Project Settings.


#include "Cpp_Hoverboard.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/CapsuleComponent.h"
#include <Kismet/KismetMathLibrary.h>
#include <Cpp_Fire.h>


// Sets default values
ACpp_Hoverboard::ACpp_Hoverboard()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;
	Hoverboard = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Hoverboard"));
	Hoverboard->SetupAttachment(Root);
	Rider = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Rider"));
	Rider->SetupAttachment(Hoverboard);
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(Hoverboard);
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
	HoverCompLT = CreateDefaultSubobject<UCpp_SC_HoverComp>(TEXT("HoverCompLT"));
	HoverCompLT->SetupAttachment(Hoverboard);
	HoverCompLB = CreateDefaultSubobject<UCpp_SC_HoverComp>(TEXT("HoverCompLB"));
	HoverCompLB->SetupAttachment(Hoverboard);
	HoverCompRT = CreateDefaultSubobject<UCpp_SC_HoverComp>(TEXT("HoverCompRT"));
	HoverCompRT->SetupAttachment(Hoverboard);
	HoverCompRB = CreateDefaultSubobject<UCpp_SC_HoverComp>(TEXT("HoverCompRB"));
	HoverCompRB->SetupAttachment(Hoverboard);
	Booster = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Boost"));
	Booster->SetupAttachment(Hoverboard);
	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	Capsule->SetupAttachment(Hoverboard);
	Collision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collision"));
	Collision->SetupAttachment(Hoverboard);

	AutoPossessPlayer = EAutoReceiveInput::Player0;

	MovingForward = true;
	InAir = false;

	Collision->OnComponentBeginOverlap.AddDynamic(this, &ACpp_Hoverboard::OnOverlapBegin);

	



}

void ACpp_Hoverboard::MoveHover(float AxisValue)
{
	
	ForwardMovementValue = AxisValue;
	if (InAir == false)
	{
		if (AxisValue > 0)
		{
			MovingForward = true;
			UGameplayStatics::PlaySoundAtLocation(this->GetWorld(), HoverSound, this->GetActorLocation());
		}
		else if (AxisValue < 0)
		{
			MovingForward = false;
			UGameplayStatics::PlaySoundAtLocation(this->GetWorld(), HoverSound, this->GetActorLocation());
		}

		FVector Forward = Hoverboard->GetForwardVector();
		Forward.Y, Forward.Z = 0;
		Hoverboard->AddForce(Forward * Speed * AxisValue, "None", true);
		Hoverboard->AddLocalRotation(FRotator(0.35, 0, 0) * AxisValue);
	}
	else 
	{
		FVector InAirForward = Hoverboard->GetForwardVector();
		InAirForward.Y, InAirForward.Z = 0;
		Hoverboard->AddLocalRotation(FRotator(3, 0, 0) * AxisValue);

	}
}

void ACpp_Hoverboard::RotateHover(float AxisValue)
{
	
	RotateMovementValue = AxisValue;
	if (InAir == false)
	{
		float Yaw = 1 * AxisValue * UKismetMathLibrary::SelectInt(1, -1, MovingForward);
		Hoverboard->AddLocalRotation(FRotator(0, Yaw, UKismetMathLibrary::SelectFloat(0, 1, ForwardMovementValue == 0) * AxisValue));
	}
	else
	{
		float InAirYaw = 7 * UKismetMathLibrary::SelectInt(1, -1, MovingForward);
		Hoverboard->AddLocalRotation(FRotator(0, InAirYaw, 0) * AxisValue);
	}
}

void ACpp_Hoverboard::NegateRotation()
{
	if (InAir == false)
	{
		Hoverboard->SetRelativeRotation(UKismetMathLibrary::RLerp(Hoverboard->GetRelativeRotation(), FRotator(0, Hoverboard->GetRelativeRotation().Yaw, 0), 0.015, true));
	}
}

void ACpp_Hoverboard::BoostSpeed()
{
	if (MovingForward && InAir == false)
	{

		Speed = UKismetMathLibrary::Lerp(2000, 10000, 1);
		Booster->Activate();
		UGameplayStatics::PlaySoundAtLocation(this->GetWorld(), BoosterSound, this->GetActorLocation());
		
	}
}

void ACpp_Hoverboard::ReturnToNormalSpeed()
{

	Speed = UKismetMathLibrary::Lerp(10000, 2000, 1);
	Booster->Deactivate();

}

void ACpp_Hoverboard::SpawnBurnMarks()
{
	if (MovingForward && Speed > 9000 && Hoverboard->GetComponentLocation().Z < 500)
	{
		GetWorld()->SpawnActor<ACpp_Fire>(BP_Fire, FVector(Hoverboard->GetComponentLocation().X, Hoverboard->GetComponentLocation().Y, 0), FRotator(0, Hoverboard->GetComponentRotation().Yaw, 0));

	}
}

void ACpp_Hoverboard::CheckInAirOrNot()
{
	float TraceLength = 2 * HoverCompRB->TraceLength;
	FVector Start = Hoverboard->GetComponentLocation();
	FVector End = Start + FVector(0, 0, Hoverboard->GetUpVector().Z) * (-1) * TraceLength;
	FHitResult OutHit;
	FCollisionQueryParams CollisionsParams;
	CollisionsParams.AddIgnoredActor(this);

	bool HasHit = GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECollisionChannel::ECC_Visibility, CollisionsParams);
	//DrawDebugDirectionalArrow(GetWorld(), Start, End, 5.0f, FColor::Red, false, 0.01f, 0, 1.f);

	InAir = !HasHit;

	if (InAir)
	{
		Booster->Deactivate();
	}
	else if (Speed == 10000)
	{
		Booster->Activate();
	}
}

void ACpp_Hoverboard::TurnX(float AxisValue)
{
	if (PlayerController)
	{
		PlayerController->AddYawInput(AxisValue * 0.75);
	}
}

void ACpp_Hoverboard::TurnY(float AxisValue)
{
    if (PlayerController)
	{
		PlayerController->AddPitchInput(AxisValue * -0.75);
	}


}

void ACpp_Hoverboard::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{

		Rider->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
		Rider->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
		Rider->SetSimulatePhysics(true);
		Rider->AddForceAtLocation(Hoverboard->GetForwardVector() * Speed * 500, this->GetActorLocation(), "None");
		
	}
}

// Called when the game starts or when spawned
void ACpp_Hoverboard::BeginPlay()
{
	Super::BeginPlay();

	Booster->Deactivate();
	PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
}

// Called every frame
void ACpp_Hoverboard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	NegateRotation();
	SpawnBurnMarks();
	CheckInAirOrNot();
}

// Called to bind functionality to input
void ACpp_Hoverboard::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveHover", this, &ACpp_Hoverboard::MoveHover);
	PlayerInputComponent->BindAxis("RotateHover", this, &ACpp_Hoverboard::RotateHover);
	PlayerInputComponent->BindAxis("TurningX", this, &ACpp_Hoverboard::TurnX);
	PlayerInputComponent->BindAxis("TurningY", this, &ACpp_Hoverboard::TurnY);
	PlayerInputComponent->BindAction("ControlSpeed", IE_Pressed, this, &ACpp_Hoverboard::BoostSpeed);
	PlayerInputComponent->BindAction("ControlSpeed", IE_Released, this, &ACpp_Hoverboard::ReturnToNormalSpeed);



}

