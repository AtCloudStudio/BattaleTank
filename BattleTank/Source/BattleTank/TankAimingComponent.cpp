// Copyright RyanXu @CloudStudio

#include "TankAimingComponent.h"
#include "TankTurret.h"
#include "TankBarrel.h"
#include "Kismet/GameplayStatics.h"
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
	LastFireTime = GetWorld()->GetTimeSeconds();
}

// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, 
ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if (AmmoAmount <= 0)
	{
		AimingState = EAimingState::OutOfAmmo;
	}
	else if (GetWorld()->GetTimeSeconds() - LastFireTime <= ReloadTime)
	{
		AimingState = EAimingState::Reloading;
	}
	else if (!ensure(Barrel)) return;
	else if (!Barrel->GetForwardVector().Equals(TargetAimDirection, 0.01f))
	{
		AimingState = EAimingState::Aiming;// if barrel is moving
	}
	else
	{
		AimingState = EAimingState::Locked;
	}
}

void UTankAimingComponent::InitializeAimingSystem
(UTankTurret* TurretToSet, UTankBarrel* BarrelToSet)
{
	Turret = TurretToSet;
	Barrel = BarrelToSet;
}

void UTankAimingComponent::AimAt(FVector TargetLocation)
{
	if (!ensure(Turret) || !ensure(Barrel)) return;

	FVector OUTLaunchVelocity(0);
	FVector StartLocation = Barrel->GetSocketLocation(FName("Launch Port"));

	if (!UGameplayStatics::SuggestProjectileVelocity(
		GetOwner(),
		OUTLaunchVelocity,
		StartLocation,
		TargetLocation,
		LaunchSpeed,
		false,
		0.0f,
		0.0f,
		ESuggestProjVelocityTraceOption::DoNotTrace)) return;
	else
	{
		TargetAimDirection = OUTLaunchVelocity.GetSafeNormal();
		auto DeltaRotator =
			TargetAimDirection.Rotation() - Barrel->GetForwardVector().Rotation();
		
		// Avoid turret always rotates the long route
		if (FMath::Abs(DeltaRotator.Yaw) < 180)
		{
			Turret->Rotate(DeltaRotator.Yaw);
		}
		else
		{
			Turret->Rotate(-DeltaRotator.Yaw);
		}

		Barrel->Elevate(DeltaRotator.Pitch);
	}
}

void UTankAimingComponent::Fire()
{
	if (!ensure(Barrel) || !ensure(ProjectileBluepirint)) return;

	if (AmmoAmount > 0 && AimingState != EAimingState::Reloading)
	{
		//Spawn a projectile at the socket location on the barrel
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBluepirint,
			Barrel->GetSocketLocation(FName("Launch Port")),
			Barrel->GetSocketRotation(FName("Launch Port")));

		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = GetWorld()->GetTimeSeconds();
		AmmoAmount--;
	}
}

EAimingState UTankAimingComponent::GetAimingState() const
{
	return AimingState;
}

int UTankAimingComponent::GetAmmoAmount() const
{
	return AmmoAmount;
}