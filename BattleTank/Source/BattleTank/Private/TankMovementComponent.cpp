// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (ensure(LeftTrack && RightTrack)) {
		LeftTrack->SetThrottle(Throw);
		RightTrack->SetThrottle(Throw);
	}
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	if (ensure(LeftTrack && RightTrack)) {
		LeftTrack->SetThrottle(Throw);
		RightTrack->SetThrottle(-Throw);
	}
}

void UTankMovementComponent::Initialise(UTankTrack * LeftTrackToSet, UTankTrack * RightTrackToSet)
{
		this->LeftTrack = LeftTrackToSet;
		this->RightTrack = RightTrackToSet;
}

void UTankMovementComponent::RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed)
{
	auto TankForwardVector = GetOwner()->GetActorForwardVector();
	auto MoveDirectionNormal = MoveVelocity.GetSafeNormal();

	auto forwardVelocity = FVector::DotProduct(TankForwardVector, MoveDirectionNormal);
	auto turnVelocity = FVector::CrossProduct(TankForwardVector, MoveDirectionNormal).Z;
	IntendMoveForward(forwardVelocity);
	IntendTurnRight(turnVelocity);
}
