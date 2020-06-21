// Copyright RyanXu @CloudStudio

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TankBarrel.h"
#include "TankAimingComponent.generated.h"

//Holds tank barrel's properties and Elevate method
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	// Called when the game starts
	//virtual void BeginPlay() override;

public:	
	// Sets default values for this component's properties
	//UTankAimingComponent();

	// Called every frame
	//virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	void SetBarrelReference(UTankBarrel* BarrelToSet);
	//TODO SetTurretReference(UTankTurret* TurretToSet);
	void AimAt(FVector TargetLocation, float LaunchSpeed);

private:
	UTankBarrel* Barrel = nullptr;

	void MoveBarrelTowards(FVector AimDirection);
};