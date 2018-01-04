// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAIController.h"
#include "Tank.h"

ATankAIController::ATankAIController() {

}
void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	ATank *ControlledTank = Cast<ATank>(GetPawn());
	ATank *PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
		if (PlayerTank && ControlledTank) {
			UE_LOG(LogTemp, Warning, TEXT("%s vectoring at %s"), *GetName(), *PlayerTank->GetName());
			MoveToActor(PlayerTank, distanceToPlayer);
			ControlledTank->AimAt(PlayerTank->GetActorLocation());
			ControlledTank->Fire();
		}

}
