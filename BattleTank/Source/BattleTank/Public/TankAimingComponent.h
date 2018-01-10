// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//enum for aiming
UENUM()
enum class EFiringStatus : uint8 {
	Reloading,
	Aiming,
	Locked,
	NoAmmo
};

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

class UTankBarrel;
class UTankTurret;
class AProjectile;
//Hold's Barrel's properties
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
	virtual void BeginPlay() override;
public:	
	// Sets default values for this component's properties
	UTankAimingComponent();
	UFUNCTION(BlueprintCallable, Category = Input)
	void Initialise(UTankBarrel *BarrelToSet, UTankTurret * TurretToSet);
	UFUNCTION(BlueprintCallable, Category = Action)
		void Fire();
	UFUNCTION(BlueprintCallable, Category = Setup)
	void AimAt(FVector AimLocation);
	UPROPERTY(BlueprintReadOnly)
	EFiringStatus FiringStatus = EFiringStatus::Reloading;
	EFiringStatus GetFiringState();
	UFUNCTION(BlueprintCallable, Category = Firing)
	uint8 GetAmmoLeft() const;

	UPROPERTY(EditAnywhere, Category = Setup)
	TSubclassOf<AProjectile> ProjectileBlueprint;
	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float LaunchSpeed = 7000;
	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float ReloadTimeInSec = 3;
	double LastFireTime = 0;
protected:

private:
	UPROPERTY(EditDefaultsOnly, Category = Firing)
	int32 ammoLeft = 5;
	UTankBarrel *Barrel = nullptr;
	UTankTurret *Turret = nullptr;
	FVector AimDirection;
	void MoveBarrel();
	bool IsBarrelMoving();
	static constexpr float aimingPrecision = 0.03; // manipulating this number changes AI's precision
	
};
