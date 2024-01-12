// Fill out your copyright notice in the Description page of Project Settings.


#include "Cpp_Hoverboard.h"

// Sets default values
ACpp_Hoverboard::ACpp_Hoverboard()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;
	Hoverboard = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Hoverboard"));
	Hoverboard->SetupAttachment(Root);
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
}

// Called when the game starts or when spawned
void ACpp_Hoverboard::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACpp_Hoverboard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACpp_Hoverboard::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

