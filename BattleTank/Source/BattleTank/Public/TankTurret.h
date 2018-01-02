// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankTurret.generated.h"

/**
 * Responsible for turret rotation
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()
public:
	//-1 = max down, +1 = max up
	void Rotate(float RelativeSpeed);

private:

UPROPERTY(EditDefaultsOnly, Category = Setup)
	float MaxDegreePerSecond = 30;
	
};
