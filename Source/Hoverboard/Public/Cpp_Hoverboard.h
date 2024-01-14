// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/SpringArmComponent.h"
#include <Kismet/GameplayStatics.h>
#include <Camera/CameraComponent.h>
#include <Cpp_SC_HoverComp.h>
#include <Cpp_Fire.h>
#include <GameFramework/FloatingPawnMovement.h>
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

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UCapsuleComponent* Capsule;

	UPROPERTY(EditAnywhere)
	UCapsuleComponent* Collision;

	UPROPERTY(EditAnywhere)
	UParticleSystemComponent* Booster;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* Hoverboard;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USkeletalMeshComponent* Rider;

	UPROPERTY(EditAnywhere)
	USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere)
	UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UCpp_SC_HoverComp* HoverCompLT;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UCpp_SC_HoverComp* HoverCompRT;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UCpp_SC_HoverComp* HoverCompLB;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UCpp_SC_HoverComp* HoverCompRB;

	UFUNCTION()
	void MoveHover(float AxisValue);

	UFUNCTION()
	void RotateHover(float AxisValue);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Speed;

	UFUNCTION()
	void NegateRotation();

	UFUNCTION()
	void BoostSpeed();

	UFUNCTION()
	void ReturnToNormalSpeed();

	UFUNCTION()
	void SpawnBurnMarks();

	UFUNCTION()
	void CheckInAirOrNot();

	UFUNCTION()
	void TurnX(float AxisValue);

	UFUNCTION()
	void TurnY(float AxisValue);

	UFUNCTION()
	void Jumping();

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	APlayerController* PlayerController;
	bool MovingForward;
	float ForwardMovementValue;
	float RotateMovementValue;
	bool InAir;

	UPROPERTY(EditAnywhere)
	UAnimMontage* JumpAnimMontage;

	UPROPERTY(EditAnywhere)
	UEnum* ActionEnum;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ACpp_Fire>BP_Fire;
	
	UPROPERTY(EditAnywhere)
	USoundBase* HoverSound;

	UPROPERTY(EditAnywhere)
	USoundBase* BoosterSound;










protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
