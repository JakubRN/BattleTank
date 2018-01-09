// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UTankAimingComponent::Initialise(UTankBarrel * BarrelToSet, UTankTurret * TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

void UTankAimingComponent::AimAt(FVector AimLocation, float Launchspeed)
{
	if (!ensure(Barrel && Turret)) return;
	FVector OutLaunchVelocity;
	auto StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	if (UGameplayStatics::SuggestProjectileVelocity(
		GetOwner(),
		OutLaunchVelocity,
		StartLocation,
		AimLocation,
		Launchspeed,
		false,
		0.0F,
		0.0F,
		ESuggestProjVelocityTraceOption::DoNotTrace,
		FCollisionResponseParams::DefaultResponseParam, TArray<AActor *>(),
		false
	)) {
		if (FiringStatus == EFiringStatus::Locked) FiringStatus = EFiringStatus::Aiming;
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrel(AimDirection);
	}
	else {
		FiringStatus = EFiringStatus::Locked;
	}
}

void UTankAimingComponent::MoveBarrel(FVector AimDirection)
{
	auto BarrelRotation = Barrel->GetForwardVector().Rotation();
	auto AimRotator = AimDirection.Rotation();
	auto DeltaRotator = AimRotator - BarrelRotation;
	if (FMath::Abs(DeltaRotator.Yaw) > 180.f) {
		DeltaRotator.Yaw -= (DeltaRotator.Yaw / FMath::Abs(DeltaRotator.Yaw)) * 360.f;
	}
	Barrel->Elevate(DeltaRotator.Pitch);
	Turret->Rotate(DeltaRotator.Yaw);

}
