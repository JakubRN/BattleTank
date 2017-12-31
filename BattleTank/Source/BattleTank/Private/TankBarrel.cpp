// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"


void UTankBarrel::Elevate(float RelativeSpeed) {
	auto relativeElevation = FMath::Clamp<float>(RelativeSpeed, -1.f, 1.f) * MaxDegreePerSecond * GetWorld()->DeltaTimeSeconds;
	auto CurrentElevation = FMath::Clamp<float>(RelativeRotation.Pitch + relativeElevation, MinElevation, MaxElevation);
	SetRelativeRotation(FRotator(CurrentElevation, 0, 0 ));

}

