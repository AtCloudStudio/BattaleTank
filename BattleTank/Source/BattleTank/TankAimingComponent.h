// Copyright RyanXu @CloudStudio

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

UENUM()
enum class EAimingState : uint8
{
	Reloading,
	Aiming,
	Locked,
	OutOfAmmo
};

class UTankTurret;
class UTankBarrel;
class AProjectile;

// Holds tank turret and barrel's properties and movement functions
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// Enumerator for aiming state
	UPROPERTY(BlueprintReadOnly, Category = "Aiming State")
	EAimingState AimingState = EAimingState::Reloading;

public:
	// Sets default values for this component's properties
	UTankAimingComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, 
	FActorComponentTickFunction* ThisTickFunction) override;
	
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void InitializeAimingSystem
	(UTankTurret* TurretToSet, UTankBarrel* BarrelToSet);

	UFUNCTION(BlueprintCallable, Category = "Firing")
	void Fire();

	UFUNCTION(BlueprintCallable, Category = "Firing")
	int GetAmmoAmount() const;
	
	void AimAt(FVector TargetLocation);

	EAimingState GetAimingState() const;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AProjectile> ProjectileBluepirint;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 8000;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float ReloadTime = 3.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	int32 AmmoAmount = 3;

	UTankTurret* Turret = nullptr;
	UTankBarrel* Barrel = nullptr;

	float LastFireTime = 0.0f;

	FVector AimDirection;
};