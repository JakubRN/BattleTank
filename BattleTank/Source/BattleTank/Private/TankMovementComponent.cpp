// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (LeftTrack && RightTrack) {
		LeftTrack->SetThrottle(Throw);
		RightTrack->SetThrottle(Throw);
	}
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	if (LeftTrack && RightTrack) {
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
	UE_LOG(LogTemp, Warning, TEXT("%s vectoring to %s"), *GetOwner()->GetName(), *MoveVelocity.ToString())
	UE_LOG(LogTemp, Warning, TEXT("movement: %f forward, %f rotation"), forwardVelocity, turnVelocity)
	IntendMoveForward(forwardVelocity);
	IntendTurnRight(turnVelocity);
}
