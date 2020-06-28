// Copyright RyanXu @CloudStudio

#include "TankSuspensionSystem.h"
#include "Components/SphereComponent.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"

ATankSuspensionSystem::ATankSuspensionSystem()
{
 	PrimaryActorTick.bCanEverTick = false;

	TankAxleSpring = CreateDefaultSubobject
		<UPhysicsConstraintComponent>(FName("Tank Axle Spring"));
	SetRootComponent(TankAxleSpring);

	SuspensionAxle =
		CreateDefaultSubobject<USphereComponent>(FName("Suspension Axle"));
	SuspensionAxle->SetupAttachment(TankAxleSpring);

	AxleWheelSpring = CreateDefaultSubobject
		<UPhysicsConstraintComponent>(FName("Axle Wheel Spring"));
	AxleWheelSpring->SetupAttachment(SuspensionAxle);

	SuspensionWheel = 
		CreateDefaultSubobject<USphereComponent>(FName("Suspension Wheel"));
	SuspensionWheel->SetupAttachment(SuspensionAxle);
}

void ATankSuspensionSystem::BeginPlay()
{
	Super::BeginPlay();

	SetupPhysicsConstraint();
}

void ATankSuspensionSystem::SetupPhysicsConstraint()
{
	if (!ensure(GetAttachParentActor())) return;

	UPrimitiveComponent* TankBody =
		Cast<UPrimitiveComponent>(GetAttachParentActor()->GetRootComponent());

	if (!ensure(TankBody)) return;

	TankAxleSpring->SetConstrainedComponents(
		TankBody, NAME_None, SuspensionAxle, NAME_None);
	AxleWheelSpring->SetConstrainedComponents(
		SuspensionAxle, NAME_None, SuspensionWheel, NAME_None);
}

void ATankSuspensionSystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}