// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <Components/SplineComponent.h>
#include "GameFramework/Actor.h"
#include "Cpp_SlideSpline.generated.h"



UCLASS()
class HOVERBOARD_API ACpp_SlideSpline : public AActor
{
	GENERATED_BODY()
	

	


	
public:	
	// Sets default values for this actor's properties
	ACpp_SlideSpline();


	UPROPERTY(EditAnywhere)
	USceneComponent* Root;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USplineComponent* Spline;

	




protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
