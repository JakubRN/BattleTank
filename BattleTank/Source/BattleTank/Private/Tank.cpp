// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Tank.h"
#include "TankBarrel.h"
#include "TankAimingComponent.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "TankTrack.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}
void ATank::BeginPlay() {
	Super::BeginPlay();
}

void ATank::Initialise(UTankBarrel * BarrelToSet, UTankAimingComponent * AimingToSet)
{
	Barrel = BarrelToSet;
	TankAimingComponent = AimingToSet;
}


void ATank::Fire()
{
	if (!ensure(Barrel)) return;
	bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSec;
	if (isReloaded) {

		LastFireTime = FPlatformTime::Seconds();
		auto projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint, 
			Barrel->GetSocketLocation(FName("Projectile")), 
			Barrel->GetSocketRotation(FName("Projectile")));
		projectile->launchProjectile(LaunchSpeed);
	}

}

void ATank::AimAt(FVector HitLocation)
{
	if ((FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSec)
	{
		if (TankAimingComponent->FiringStatus == EFiringStatus::Reloading) TankAimingComponent->FiringStatus = EFiringStatus::Aiming;
	}
	else {
		if (TankAimingComponent->FiringStatus == EFiringStatus::Aiming) TankAimingComponent->FiringStatus = EFiringStatus::Reloading;
	}
	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
}

