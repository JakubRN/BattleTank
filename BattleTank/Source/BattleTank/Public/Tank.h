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

	virtual void SetupPlayerInputComponent(class UInputComponent* CurrentInputComponent) override;

public:
	// Sets default values for this pawn's properties
	ATank();

	// Called to bind functionality to input



	UPROPERTY(EditAnywhere, Category = Setup)
	TSubclassOf<AProjectile> ProjectileBlueprint;

	UFUNCTION(BlueprintCallable, Category = Setup)
	void setBarrelReference(UTankBarrel *BarrelToSet);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void setTurretReference(UTankTurret *TurretToSet);

	UFUNCTION(BlueprintCallable, Category = Action)
	void Fire();

	UPROPERTY(EditDefaultsOnly, Category = Firing)
		float LaunchSpeed = 4000;
	UPROPERTY(EditDefaultsOnly, Category = Firing)
		double ReloadTimeInSec = 3;
	double LastFireTime = 0;


	void AimAt(FVector HitLocation);
protected:
	UPROPERTY(BlueprintReadOnly)
	UTankAimingComponent *TankAimingComponent = nullptr;
	UTankBarrel *Barrel = nullptr;

};
