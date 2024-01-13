// Fill out your copyright notice in the Description page of Project Settings.


#include "Cpp_Hoverboard.h"
#include <Kismet/KismetMathLibrary.h>

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
	FloatingMovemnt = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("FloatingMovemnt"));

	AutoPossessPlayer = EAutoReceiveInput::Player0;

	MovingForward = true;

	



}

void ACpp_Hoverboard::MoveHover(float AxisValue)
{

	Hoverboard->AddForce(Hoverboard->GetForwardVector() * Speed * AxisValue, "None", true);
	if (AxisValue >= 0) MovingForward = true;
	else MovingForward = false;

}

void ACpp_Hoverboard::RotateHover(float AxisValue)
{
	float Yaw = UKismetMathLibrary::SelectFloat(1, -1, MovingForward);
	Hoverboard->AddLocalRotation(FRotator(0, Yaw, 1.5) * AxisValue);
}

void ACpp_Hoverboard::NegateRotation()
{

	Hoverboard->SetRelativeRotation(UKismetMathLibrary::RLerp(Hoverboard->GetRelativeRotation(), FRotator(0, Hoverboard->GetRelativeRotation().Yaw, 0), 0.015, true));

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

// Called when the game starts or when spawned
void ACpp_Hoverboard::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
}

// Called every frame
void ACpp_Hoverboard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	NegateRotation();
}

// Called to bind functionality to input
void ACpp_Hoverboard::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveHover", this, &ACpp_Hoverboard::MoveHover);
	PlayerInputComponent->BindAxis("RotateHover", this, &ACpp_Hoverboard::RotateHover);
	PlayerInputComponent->BindAxis("TurningX", this, &ACpp_Hoverboard::TurnX);
	PlayerInputComponent->BindAxis("TurningY", this, &ACpp_Hoverboard::TurnY);


}

