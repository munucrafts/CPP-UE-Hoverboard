// Fill out your copyright notice in the Description page of Project Settings.


#include "Cpp_SC_HoverComp.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values for this component's properties
UCpp_SC_HoverComp::UCpp_SC_HoverComp()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	


}





// Called when the game starts
void UCpp_SC_HoverComp::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UCpp_SC_HoverComp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector Start = this->GetComponentLocation();  
	FVector End = Start + this->GetUpVector() * (-1) * TraceLength;
	FHitResult OutHit;
	FCollisionQueryParams CollisionsParams;
	CollisionsParams.AddIgnoredActor(this->GetOwner());

	bool HasHit = GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECollisionChannel::ECC_Visibility, CollisionsParams);
	//DrawDebugDirectionalArrow(GetWorld(), Start, End, 5.0f, FColor::Red, false, 0.01f, 0, 1.f);

	float LerpAlpha = (OutHit.Location - this->GetComponentLocation()).Size() / TraceLength;
	float LerpReturn = UKismetMathLibrary::Lerp(HoverForce, 0, LerpAlpha);
	FVector Force = LerpReturn * OutHit.ImpactNormal;


	if (HasHit)
	{
		LocMesh->AddForceAtLocation(Force, this->GetComponentLocation());
		LocMesh->SetLinearDamping(1);
		LocMesh->SetAngularDamping(100);
	}
	else 
	{
		LocMesh->AddForceAtLocation(FVector(0, 0, -0.1 * HoverForce), this->GetComponentLocation());
		LocMesh->SetLinearDamping(1);
		LocMesh->SetAngularDamping(100);
	}










}

