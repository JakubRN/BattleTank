// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

//Forward declarations
class UTankBarrel;
class UTankAimingComponent;
class UTankTurret;
class UTankTrack;
class UTankMovementComponent;
class AProjectile;
UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	// Called to bind functionality to input

	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	UPROPERTY(EditAnywhere, Category = Setup)
	TSubclassOf<AProjectile> ProjectileBlueprint;

	UFUNCTION(BlueprintCallable, Category = Setup)
	void setBarrelReference(UTankBarrel *BarrelToSet);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void setTurretReference(UTankTurret *TurretToSet);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void setLeftTrackReference(UTankTrack *TrackToSet);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void setRightTrackReference(UTankTrack *TrackToSet);

	UFUNCTION(BlueprintCallable, Category = Action)
	void Fire();

	UPROPERTY(EditDefaultsOnly, Category = Firing)
		float LaunchSpeed = 4000;
	UPROPERTY(EditDefaultsOnly, Category = Firing)
		double ReloadTimeInSec = 3;
	double LastFireTime = 0;


	void AimAt(FVector HitLocation);
protected:
	UTankAimingComponent *TankAimingComponent = nullptr;
	UTankBarrel *Barrel = nullptr;
	UTankTrack *LeftTrack = nullptr;
	UTankTrack *RightTrack = nullptr;
	UPROPERTY(BlueprintReadOnly)
	UTankMovementComponent *TankMovementComponent = nullptr;
};
