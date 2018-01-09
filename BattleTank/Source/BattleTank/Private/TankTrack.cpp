// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTrack.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankTrack::BeginPlay()
{
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::ApplySidewaysForce(float DeltaTime)
{
	auto SlidingSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
	auto CorrectionAcceleration = -(SlidingSpeed / DeltaTime) *  GetRightVector();
	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto CorrectionForce = (TankRoot->GetMass() * CorrectionAcceleration) / 2;
	TankRoot->AddForce(CorrectionForce);
}

void UTankTrack::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult & Hit)
{
	ApplySidewaysForce(GetWorld()->GetDeltaSeconds());
	DriveTrack();
	currentThrottle = 0;
}

void UTankTrack::SetThrottle(float Throttle)
{
	currentThrottle = FMath::Clamp<float>(currentThrottle + Throttle, -1.f, 1.f);
}

void UTankTrack::DriveTrack()
{
	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto ForceToApply = GetForwardVector() * TankRoot->GetMass() * TrackMaxDrivingAcceleration * currentThrottle;
	TankRoot->AddForceAtLocation(ForceToApply, GetComponentLocation());
}
