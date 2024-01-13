
// Fill out your copyright notice in the Description page of Project Settings.


#include "Cpp_Fire.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/DecalComponent.h"

// Sets default values
ACpp_Fire::ACpp_Fire()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;
	Fire = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Fire"));
	Fire->SetupAttachment(Root);
	FireMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FireMesh"));
	FireMesh->SetupAttachment(Root);

	this->SetLifeSpan(5);
	
}

// Called when the game starts or when spawned
void ACpp_Fire::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACpp_Fire::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

