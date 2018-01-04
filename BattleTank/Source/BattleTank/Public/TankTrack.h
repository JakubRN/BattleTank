// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
		//Sets a throttle between -1 and 1
		UFUNCTION(BlueprintCallable, Category = Input)
		void SetThrottle(float Throttle);
	
		//Force to drive the tracks
		UPROPERTY(EditDefaultsOnly, Category = Setup)
		float TrackMaxDrivingForce = 50000000; // assuming 50T tank
		float lastMovementTime = 0.f;
};
