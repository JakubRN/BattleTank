// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Tank.h"
#include "TankBarrel.h"
#include "TankAimingComponent.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "TankTrack.h"
#include "TankMovementComponent.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
	//TankMovementComponent = CreateDefaultSubobject<UTankMovementComponent>(FName("Hoho Movement Component"));
}


// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(class UInputComponent* CurrentInputComponent)
{
	Super::SetupPlayerInputComponent(CurrentInputComponent);

}


void ATank::setBarrelReference(UTankBarrel * BarrelToSet)
{
	TankAimingComponent->setBarrelReference(BarrelToSet);
	Barrel = BarrelToSet;
}

void ATank::setTurretReference(UTankTurret * TurretToSet)
{
	TankAimingComponent->setTurretReference(TurretToSet);
}

void ATank::Fire()
{
	bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSec;
	if (Barrel && isReloaded) {

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

