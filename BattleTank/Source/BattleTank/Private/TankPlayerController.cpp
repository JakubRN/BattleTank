// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Tank.h"
#include "TankPlayerController.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	ATank *ControlledTank = GetControlledTank();
	if (!ControlledTank) {
		UE_LOG(LogTemp, Warning, TEXT("Tank not posessed"));
		return;
	UE_LOG(LogTemp, Warning, TEXT("Hello there %s"), *ControlledTank->GetName());
	}
}

void ATankPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	AimTowardsCrosshair();
}

ATank * ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) { return; }
	FVector HitLocation;
	if (GetSightRayHitLocation(OUT HitLocation)) {
		GetControlledTank()->AimAt(HitLocation);
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
		if(GetLookVectorHitLocation(WorldDirection,OUT OutHitLocation)) {
			return true;
		}
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
		ECC_Visibility)
		)
	{
		OutHitLocation = HitObject.Location;
		return true;
	}
	else {
		OutHitLocation = FVector(0);
		return false;
	}
}


