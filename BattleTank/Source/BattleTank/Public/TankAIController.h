// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "AIController.h"
#include "TankAIController.generated.h"

UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

public:
	ATankAIController();
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;
protected:
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float distanceToPlayer = 7000.f;
private:
};
