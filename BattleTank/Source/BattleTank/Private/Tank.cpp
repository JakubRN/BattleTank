// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Tank.h"


float ATank::GetHealthPercent() const
{
	return (float)CurrentHealth / (float)MaxHealth;
}

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}
void ATank::BeginPlay() {
	Super::BeginPlay();
	CurrentHealth = MaxHealth;
}
float ATank::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) {

	int32 DamageApplied = FMath::Clamp(FPlatformMath::RoundToInt(Damage), 0, CurrentHealth);
	CurrentHealth -= DamageApplied;
	UE_LOG(LogTemp, Warning, TEXT("DamageL %d, current Health:%d"), DamageApplied, CurrentHealth)
	if (CurrentHealth <= 0) {
		thisTankDied.Broadcast();
	}
		return DamageApplied;
}