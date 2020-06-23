// Copyright RyanXu @CloudStudio

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TankAimingComponent.generated.h"

class UTankTurret;
class UTankBarrel;

//Holds tank turret and barrel's properties and movement functions
UCLASS( ClassGroup = (Custom), meta = (BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	void SetBarrelReference(UTankBarrel* BarrelToSet);
	void SetTurretReference(UTankTurret* TurretToSet);
	void AimAt(FVector TargetLocation, float LaunchSpeed);

private:
	UTankTurret* Turret = nullptr;
	UTankBarrel* Barrel = nullptr;
};