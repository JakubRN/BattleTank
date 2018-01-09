// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"



class ATank;
class UTankAimingComponent;

UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
protected:
	UFUNCTION(BlueprintCallable, Category = Setup)
	ATank *GetControlledTank() const;

	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
		void FoundAimingComponent(UTankAimingComponent *AimingComponentReference);
private:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;
	
	//moves the barrel to aim at the point where crosshair intersects the world
	void AimTowardsCrosshair();

	bool GetSightRayHitLocation(FVector &OutHitLocation) const;
	bool GetLookDirection(FVector2D ScreenLocation, FVector &LookDirection) const;
	bool GetLookVectorHitLocation(FVector &LookDirection, FVector &OutHitLocation) const;
	UPROPERTY(EditDefaultsOnly)
	float CrosshairXLocation = 0.5;
	UPROPERTY(EditDefaultsOnly)
	float CrosshairYLocation = 0.36;
	UPROPERTY(EditDefaultsOnly)
	float LineTraceRange = 1000000;

};
