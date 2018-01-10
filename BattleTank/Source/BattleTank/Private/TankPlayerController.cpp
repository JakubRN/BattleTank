// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankPlayerController.h"
#include "TankAimingComponent.h"
#include "Tank.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (ensure(AimingComponent)) {
		FoundAimingComponent(AimingComponent);
	}
}

void ATankPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	AimTowardsCrosshair();
}
void ATankPlayerController::SetPawn(APawn *InPawn) {
	Super::SetPawn(InPawn);
	auto posessedTank = Cast<ATank>(InPawn);
	if (!ensure(posessedTank)) { return; }
	posessedTank->thisTankDied.AddUniqueDynamic(this, &ATankPlayerController::OnTankDead);
}

void ATankPlayerController::OnTankDead() {
	if (!GetPawn()) { return; }
	StartSpectatingOnly();
}
void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetPawn()) { return; }
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }
	FVector HitLocation;
	if (GetSightRayHitLocation(OUT HitLocation)) {
		AimingComponent->AimAt(HitLocation);
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector & OutHitLocation) const
{
	
	OutHitLocation = FVector(1.0);
	int32 ViewportX, ViewportY;
	GetViewportSize(ViewportX, ViewportY);
	auto CrosshairScreenLocation = FVector2D(ViewportX * CrosshairXLocation, ViewportY * CrosshairYLocation);
	FVector WorldDirection;
	if (GetLookDirection(CrosshairScreenLocation, OUT WorldDirection)) {
		return GetLookVectorHitLocation(WorldDirection, OUT OutHitLocation);
	}
	return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector & LookDirection) const
{
	FVector WorldLocation;
	return (DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, WorldLocation, LookDirection));
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector & LookDirection, FVector & OutHitLocation) const
{
	FHitResult HitObject;
	FVector StartPosition = PlayerCameraManager->GetCameraLocation();
	FVector EndPosition = (LineTraceRange * LookDirection + StartPosition);
	if (GetWorld()->LineTraceSingleByChannel(
		HitObject,
		StartPosition, 
		EndPosition, 
		ECC_Camera
		))
	{
		OutHitLocation = HitObject.Location;
		return true;
	}
	else {
		OutHitLocation = FVector(0);
		return false;
	}
}


