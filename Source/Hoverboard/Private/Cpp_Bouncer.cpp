// Fill out your copyright notice in the Description page of Project Settings.


#include "Cpp_Bouncer.h"
#include "Particles/ParticleSystemComponent.h"
#include <Cpp_Hoverboard.h>



// Sets default values
ACpp_Bouncer::ACpp_Bouncer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;
	BouncerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BouncerMesh"));
	BouncerMesh->SetupAttachment(Root);
	BouncerParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("BouncerParticle"));
	BouncerParticle->SetupAttachment(Root);
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxCollision->SetupAttachment(Root);

	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &ACpp_Bouncer::OnOverlapBegin);


}

void ACpp_Bouncer::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	UE_LOG(LogTemp, Warning, TEXT("ddddddd"));
	if (Cast<ACpp_Hoverboard>(OtherActor))
	{
		
		AddBounceForce(OtherComp);
	}

}

void ACpp_Bouncer::AddBounceForce(UPrimitiveComponent* Comp)
{
	
	//Comp->AddForceAtLocation(BounceForce * this->GetActorUpVector(), Comp->GetComponentLocation());

}

// Called when the game starts or when spawned
void ACpp_Bouncer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACpp_Bouncer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

