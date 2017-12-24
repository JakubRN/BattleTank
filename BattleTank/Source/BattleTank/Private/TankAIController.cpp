// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAIController.h"
#include "Tank.h"

ATankAIController::ATankAIController() {

}
void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	ATank *controlledTank = GetControlledTank();
	if (!controlledTank) return;
	UE_LOG(LogTemp, Warning, TEXT("AI posessed tank: %s"), *controlledTank->GetName());
	ATank *MainPlayer = GetPlayerTank();
	if (!MainPlayer) {
		UE_LOG(LogTemp, Warning, TEXT("Player tank not detected"))
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Player tank: %s"), *MainPlayer->GetName());
	}
}

void ATankAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
		if (GetPlayerTank()) {
			GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());
		}
}

ATank * ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank * ATankAIController::GetPlayerTank() const
{
	return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}
