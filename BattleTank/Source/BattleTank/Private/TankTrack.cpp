// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTrack.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankTrack::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	auto SlidingSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
	auto CorrectionAcceleration = -(SlidingSpeed / DeltaTime) *  GetRightVector();
	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto CorrectionForce = (TankRoot->GetMass() * CorrectionAcceleration);
	//TankRoot->AddForceAtLocation(CorrectionForce, GetComponentLocation());
}

void UTankTrack::SetThrottle(float Throttle)
{
	if (lastMovementTime == GetWorld()->GetDeltaSeconds()) {
		return;
	}
	
	if (FMath::Abs(Throttle) > 0.3) {
		auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
		
		//auto SlidingSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
		//auto CorrectionAcceleration = -(SlidingSpeed / GetWorld()->DeltaTimeSeconds) *  GetRightVector();
		//auto CorrectionForce = (TankRoot->GetMass() * CorrectionAcceleration);
		//TankRoot->AddForce(CorrectionForce);

		lastMovementTime = GetWorld()->GetDeltaSeconds();
		Throttle = FMath::Clamp<float>(Throttle, -0.85f, 1.f);
		auto ForceToApply = GetForwardVector() * TankRoot->GetMass() * TrackMaxDrivingAcceleration * Throttle;
		TankRoot->AddForceAtLocation(ForceToApply, GetComponentLocation());

	}	


}
