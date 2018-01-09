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
private:
	UTankTrack();
	virtual void BeginPlay() override;
	void ApplySidewaysForce(float DeltaTime);
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

public:
		//Sets a throttle between -1 and 1
		UFUNCTION(BlueprintCallable, Category = Input)
		void SetThrottle(float Throttle);

		void DriveTrack();
	
		//Force to drive the tracks
		UPROPERTY(EditDefaultsOnly, Category = Setup)
		float TrackMaxDrivingAcceleration = 800;
		float lastMovementTime = 0.f;
		float currentThrottle = 0;
};
