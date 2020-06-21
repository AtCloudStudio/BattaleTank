// Copyright RyanXu @CloudStudio

#include "TankAimingComponent.h"

// //Sets default values for this component's properties
//UTankAimingComponent::UTankAimingComponent()
//{
//	// Set this component to be initialized when the game starts, 
//	// and to be ticked every frame. You can turn these features off 
//	// to improve performance if you don't need them.
//	PrimaryComponentTick.bCanEverTick = false;
//}
//
//// Called when the game starts
//void UTankAimingComponent::BeginPlay()
//{
//	Super::BeginPlay();
//}
//
//// Called every frame
//void UTankAimingComponent::TickComponent(float DeltaTime, 
//	ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
//{
//	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
//}
//
//void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
//{
//	Barrel = BarrelToSet;
//}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	Barrel = BarrelToSet;
}

void UTankAimingComponent::AimAt(FVector TargetLocation, float LaunchSpeed)
{
	if (!Barrel)
	{
		return;
	}

	FVector OUTLaunchVelocity(0);
	FVector StartLocation = Barrel->GetSocketLocation(FName("Launch Port"));

	//Calculate OUTLaunchVelocity
	if (UGameplayStatics::SuggestProjectileVelocity(
		GetOwner(),
		OUTLaunchVelocity,
		StartLocation,
		TargetLocation,
		LaunchSpeed,
		false,
		0.0f,
		0.0f,
		ESuggestProjVelocityTraceOption::DoNotTrace))
	{
		auto AimDirection = OUTLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
	}
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	//Calculate difference between current barrel rotation and AimDirection
	auto DeltaRotator = 
		AimDirection.Rotation() - Barrel->GetForwardVector().Rotation();

	Barrel->Elevate(1.0f);	//TODO remove hardcode number
}