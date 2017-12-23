// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankBarrel;
class UTankAimingComponent;
UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input

	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	UFUNCTION(BlueprintCallable, Category = Setup)
	void setBarrelReference(UTankBarrel *BarrelToSet);

	UPROPERTY(EditAnywhere, Category = Firing)
		float LaunchSpeed = 100000;
	void AimAt(FVector HitLocation);
protected:
	UTankAimingComponent *TankAimingComponent = nullptr;
	
};
