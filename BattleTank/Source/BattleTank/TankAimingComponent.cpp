// Copyright RyanXu @CloudStudio

#include "TankAimingComponent.h"
#include "TankTurret.h"
#include "TankBarrel.h"

void UTankAimingComponent::SetTurretReference(UTankTurret* TurretToSet)
{
	Turret = TurretToSet;
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	Barrel = BarrelToSet;
}

void UTankAimingComponent::AimAt(FVector TargetLocation, float LaunchSpeed)
{
	if (!Turret)
	{
		UE_LOG(LogTemp, Error, TEXT("No turret on %s"), *GetOwner()->GetName());

		return;
	}
	else if (!Barrel)
	{
		UE_LOG(LogTemp, Error, TEXT("No Barrel on %s"), *GetOwner()->GetName());

		return;
	}

	FVector OUTLaunchVelocity(0);
	FVector StartLocation = Barrel->GetSocketLocation(FName("Launch Port"));

	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
		GetOwner(),
		OUTLaunchVelocity,
		StartLocation,
		TargetLocation,
		LaunchSpeed,
		false,
		0.0f,
		0.0f,
		ESuggestProjVelocityTraceOption::DoNotTrace);

	if (!bHaveAimSolution)
	{
		return;
	}
	else
	{
		auto AimDirection = OUTLaunchVelocity.GetSafeNormal();
		auto DeltaRotator =
			AimDirection.Rotation() - Barrel->GetForwardVector().Rotation();

		Turret->Rotate(DeltaRotator.Yaw);
		Barrel->Elevate(DeltaRotator.Pitch);
	}
}