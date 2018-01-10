// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAIController.h"
#include "TankAimingComponent.h"
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
	auto ControlledTank = GetPawn();
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	if ((PlayerTank && ControlledTank)) {
		MoveToActor(PlayerTank, distanceToPlayer);
		auto aimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
		aimingComponent->AimAt(PlayerTank->GetActorLocation() + FVector(0,0,150));
		if (aimingComponent->GetFiringState() == EFiringStatus::Locked) {
			aimingComponent->Fire();
		}
	}
}

void ATankAIController::SetPawn(APawn * InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn) {
		auto posessedTank = Cast<ATank>(InPawn);
		if (!ensure(posessedTank)) { return; }
		posessedTank->thisTankDied.AddUniqueDynamic(this, &ATankAIController::OnTankDead);
	}
}

void ATankAIController::OnTankDead()
{
	if (!GetPawn()) { return; }
	GetPawn()->DetachFromControllerPendingDestroy();
}
