// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */

//Responsible for Barrel's elevation
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
	
public:
	//-1 = max down, +1 = max up
	void Elevate(float RelativeSpeed);

private:
	UPROPERTY(EditAnywhere, Category = Setup)
		float MaxDegreePerSecond = 30;
	UPROPERTY(EditAnywhere, Category = Setup)
		float MaxElevation = 35;
	UPROPERTY(EditAnywhere, Category = Setup)
		float MinElevation =  0;
};
