// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAIController.h"
#include "TankAimingComponent.h"

ATankAIController::ATankAIController() {

}
void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	auto ControlledTank = GetPawn();
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (ensure(PlayerTank && ControlledTank)) {
		MoveToActor(PlayerTank, distanceToPlayer);
		auto aimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
		aimingComponent->AimAt(PlayerTank->GetActorLocation());
		if (aimingComponent->GetFiringState() == EFiringStatus::Locked) {
			UE_LOG(LogTemp, Warning, TEXT("AI FIRING"))
			aimingComponent->Fire();
		}
	}

}
