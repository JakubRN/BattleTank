// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//enum for aiming
UENUM()
enum class EFiringStatus : uint8 {
	Reloading,
	Aiming,
	Locked
};

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

class UTankBarrel;
class UTankTurret;
//Hold's Barrel's properties
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()
public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	void setBarrelReference(UTankBarrel *BarrelToSet);
	void setTurretReference(UTankTurret * TurretToSet);
	void AimAt(FVector AimLocation, float Launchspeed);
	UPROPERTY(BlueprintReadOnly)
	EFiringStatus FiringStatus = EFiringStatus::Reloading;
protected:

private:
	UTankBarrel *Barrel = nullptr;
	UTankTurret *Turret = nullptr;
	void MoveBarrel(FVector AimDirection);
	
};
