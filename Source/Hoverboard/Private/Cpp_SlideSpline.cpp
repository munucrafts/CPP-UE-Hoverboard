// Fill out your copyright notice in the Description page of Project Settings.


#include "Cpp_SlideSpline.h"

void ACpp_SlideSpline::AddSplineMeshes()
{
}



// Sets default values
ACpp_SlideSpline::ACpp_SlideSpline()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;
	Spline = CreateDefaultSubobject<USplineComponent>(TEXT("Spline"));
	Spline->SetupAttachment(Root);
	

}

// Called when the game starts or when spawned
void ACpp_SlideSpline::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACpp_SlideSpline::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

