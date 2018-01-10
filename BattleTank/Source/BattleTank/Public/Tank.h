
#pragma once

#include "GameFramework/Pawn.h"
#include "Tank.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDead);

//Controls Tank behaviour
UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()
public:
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	virtual void BeginPlay() override;
	UFUNCTION(BlueprintPure, Category = "Health")
	float GetHealthPercent() const;
	FTankDead thisTankDied;
private:
	ATank();

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		int32 MaxHealth = 100;
	UPROPERTY(VisibleAnywhere, Category = "Health")
		int32 CurrentHealth = 0;
};
