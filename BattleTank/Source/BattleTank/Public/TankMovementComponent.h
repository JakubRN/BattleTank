// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"


class UTankTrack;
/**
 * responsible for driving the tank tracks
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()


public:
	UFUNCTION(BlueprintCallable, Category = Input)
	void IntendMoveForward( float Throw );
	UFUNCTION(BlueprintCallable, Category = Input)
		void IntendTurnRight(float Throw);
	UFUNCTION(BlueprintCallable, Category = Setup)
	void Initialise(UTankTrack *LeftTrack, UTankTrack *RightTrack);
private:
	//called by the AI controllers for the pathfinding logic
	void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;

	UTankTrack *LeftTrack = nullptr;
	UTankTrack *RightTrack = nullptr;
	float lastForwardMovementTime = 0.f;
	float lastRotateTime = 0.f;
};