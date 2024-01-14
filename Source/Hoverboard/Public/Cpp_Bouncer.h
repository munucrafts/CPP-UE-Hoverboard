// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <Components/BoxComponent.h>
#include "Cpp_Bouncer.generated.h"


UCLASS()
class HOVERBOARD_API ACpp_Bouncer : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACpp_Bouncer();

	UPROPERTY(EditAnywhere)
	USceneComponent* Root;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* BouncerMesh;

	UPROPERTY(EditAnywhere)
	UParticleSystemComponent* BouncerParticle;

	UPROPERTY(EditAnywhere)
	UBoxComponent* BoxCollision;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void AddBounceForce(UPrimitiveComponent* Comp);

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float BounceForce;

	




protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
