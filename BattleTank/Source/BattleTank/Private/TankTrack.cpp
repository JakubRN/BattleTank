// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTrack.h"

void UTankTrack::SetThrottle(float Throttle)
{
	if ((lastMovementTime == GetWorld()->GetDeltaSeconds()) || FMath::Abs(Throttle) < 0.2) {
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("THROTTLE:%f"), Throttle);
	lastMovementTime = GetWorld()->GetDeltaSeconds();
	Throttle = FMath::Clamp<float>(Throttle, -0.7f, 1.f);
	auto ForceToApply = GetForwardVector() * TrackMaxDrivingForce * Throttle;
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceToApply, GetComponentLocation());
}
