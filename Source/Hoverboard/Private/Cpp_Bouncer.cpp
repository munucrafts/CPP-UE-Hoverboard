// Fill out your copyright notice in the Description page of Project Settings.


#include "Cpp_Bouncer.h"
#include "Particles/ParticleSystemComponent.h"
#include <Cpp_Hoverboard.h>
#include <Components/BoxComponent.h>



// Sets default values
ACpp_Bouncer::ACpp_Bouncer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;
	BouncerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BouncerMesh"));
	BouncerMesh->SetupAttachment(Root);
	BouncerParticles = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("BouncerParticle"));
	BouncerParticles->SetupAttachment(Root);
	BouncerCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BouncerCollision"));
	BouncerCollision->SetupAttachment(Root);
	BouncerCollision->OnComponentBeginOverlap.AddDynamic(this, &ACpp_Bouncer::OnOverlapBegin);


}

void ACpp_Bouncer::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<ACpp_Hoverboard>(OtherActor))
	{
		AddBounceForce(OtherComp);
	}
}

void ACpp_Bouncer::AddBounceForce(UPrimitiveComponent* Comp)
{
	UE_LOG(LogTemp, Warning, TEXT("SSSSddsdsdS"));
	if (Comp->GetClass() == (UStaticMeshComponent::StaticClass()))
	{
		UE_LOG(LogTemp, Warning, TEXT("SSSSS"));
		Comp->SetSimulatePhysics(true);
		Comp->AddForceAtLocation(BounceForce * 100000 * this->GetActorUpVector(), Comp->GetComponentLocation());
	}
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

