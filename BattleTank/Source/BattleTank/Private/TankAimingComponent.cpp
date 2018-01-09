// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
}

void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
	LastFireTime = FPlatformTime::Seconds();
}
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTimeInSec) {
		FiringStatus = EFiringStatus::Reloading;
	}
	else if(IsBarrelMoving()){
		FiringStatus = EFiringStatus::Aiming;
	}
	else {
		FiringStatus = EFiringStatus::Locked;
	}

}
void UTankAimingComponent::Initialise(UTankBarrel * BarrelToSet, UTankTurret * TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

void UTankAimingComponent::AimAt(FVector AimLocation)
{
	if (!ensure(Barrel && Turret)) return;
	FVector OutLaunchVelocity;
	auto StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	if (UGameplayStatics::SuggestProjectileVelocity(
		GetOwner(),
		OutLaunchVelocity,
		StartLocation,
		AimLocation,
		LaunchSpeed,
		false,
		0.0F,
		0.0F,
		ESuggestProjVelocityTraceOption::DoNotTrace,
		FCollisionResponseParams::DefaultResponseParam, TArray<AActor *>(),
		false
	)) {
		this->AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrel();
	}
}

EFiringStatus UTankAimingComponent::GetFiringState()
{
	return FiringStatus;
}

void UTankAimingComponent::MoveBarrel()
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
bool UTankAimingComponent::IsBarrelMoving()
{
	if (!ensure(Barrel)) return false;
	return !AimDirection.Equals(Barrel->GetForwardVector(), aimingPrecision);
}
void UTankAimingComponent::Fire() {
	if (!ensure(Barrel)) return;
	if (FiringStatus == EFiringStatus::Aiming || FiringStatus == EFiringStatus::Locked) {
		LastFireTime = FPlatformTime::Seconds();
		auto projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile")));
		projectile->launchProjectile(LaunchSpeed);
	}
}
