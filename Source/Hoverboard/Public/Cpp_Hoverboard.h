// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/SpringArmComponent.h"
#include <Camera/CameraComponent.h>
#include <Cpp_SC_HoverComp.h>
#include "Cpp_Hoverboard.generated.h"



UCLASS()
class HOVERBOARD_API ACpp_Hoverboard : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACpp_Hoverboard();

	UPROPERTY(EditAnywhere)
	USceneComponent* Root;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Hoverboard;

	UPROPERTY(EditAnywhere)
	USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere)
	UCameraComponent* Camera;

	UPROPERTY(EditAnywhere)
	UCpp_SC_HoverComp* HoverCompLT;

	UPROPERTY(EditAnywhere)
	UCpp_SC_HoverComp* HoverCompRT;

	UPROPERTY(EditAnywhere)
	UCpp_SC_HoverComp* HoverCompLB;

	UPROPERTY(EditAnywhere)
	UCpp_SC_HoverComp* HoverCompRB;












protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
