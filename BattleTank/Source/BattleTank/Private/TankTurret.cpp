// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTurret.h"

void UTankTurret::Rotate(float RelativeSpeed)
{
	constexpr int multiplier = 9;
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -multiplier, multiplier);
	auto RotationChange = RelativeSpeed * MaxDegreePerSecond / multiplier * GetWorld()->DeltaTimeSeconds;
	auto Rotation = RelativeRotation.Yaw + RotationChange;
	SetRelativeRotation(FRotator(0, Rotation, 0));
}
