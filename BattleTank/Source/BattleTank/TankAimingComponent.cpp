// Copyright RyanXu @CloudStudio

#include "TankAimingComponent.h"
#include "TankTurret.h"
#include "TankBarrel.h"
#include "Projectile.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, 
	ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UTankAimingComponent::InitializeAimingSystem
(UTankTurret* TurretToSet, UTankBarrel* BarrelToSet)
{
	Turret = TurretToSet;
	Barrel = BarrelToSet;
}

void UTankAimingComponent::AimAt(FVector TargetLocation)
{
	if (!ensure(Turret) || !ensure(Barrel))
	{
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

void UTankAimingComponent::Fire()
{
	if (!ensure(Barrel) || !ensure(ProjectileBluepirint))
	{
		return;
	}

	if (GetWorld()->GetTimeSeconds() - LastFireTime >= ReloadTime)
	{
		//Spawn a projectile at the socket location on the barrel
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBluepirint,
			Barrel->GetSocketLocation(FName("Launch Port")),
			Barrel->GetSocketRotation(FName("Launch Port")));

		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = GetWorld()->GetTimeSeconds();
	}
}