// Copyright RyanXu @CloudStudio

#include "TankSuspensionSystem.h"
#include "Components/SphereComponent.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"

ATankSuspensionSystem::ATankSuspensionSystem()
{
 	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickGroup = TG_PostPhysics;

	TankAxleSpring = CreateDefaultSubobject
		<UPhysicsConstraintComponent>(FName("Tank Axle Spring"));
	SetRootComponent(TankAxleSpring);

	WheelAxle = CreateDefaultSubobject<USphereComponent>(FName("Wheel Axle"));
	WheelAxle->SetupAttachment(TankAxleSpring);

	AxleWheelSpring = CreateDefaultSubobject
		<UPhysicsConstraintComponent>(FName("Axle Wheel Spring"));
	AxleWheelSpring->SetupAttachment(WheelAxle);

	Wheel = CreateDefaultSubobject<USphereComponent>(FName("Wheel"));
	Wheel->SetupAttachment(AxleWheelSpring);
}

void ATankSuspensionSystem::BeginPlay()
{
	Super::BeginPlay();

	SetupPhysicsConstraint();

	if (!ensure(Wheel)) return;

	Wheel->SetNotifyRigidBodyCollision(true);
	Wheel->OnComponentHit.AddDynamic(this, &ATankSuspensionSystem::OnHit);
}

void ATankSuspensionSystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GetWorld()->TickGroup == TG_PostPhysics)
	{
		TotalForcePerFrame = 0;
	}
}

void ATankSuspensionSystem::SetupPhysicsConstraint()
{
	if (!ensure(GetAttachParentActor())) return;

	UPrimitiveComponent* TankBody =
		Cast<UPrimitiveComponent>(GetAttachParentActor()->GetRootComponent());

	if (!ensure(TankBody)) return;

	TankAxleSpring->SetConstrainedComponents(
		TankBody, NAME_None, WheelAxle, NAME_None);
	AxleWheelSpring->SetConstrainedComponents(
		WheelAxle, NAME_None, Wheel, NAME_None);
}

void ATankSuspensionSystem::OnHit(
	UPrimitiveComponent* HitComponent, 
	AActor* OtherActor, 
	UPrimitiveComponent* OtherComponent, 
	FVector NormalImpulse, 
	const FHitResult& Hit)
{
	//Apply driving force when hit the ground
	Wheel->AddForce(WheelAxle->GetForwardVector() * TotalForcePerFrame);
}

void ATankSuspensionSystem::AddDrivingForce(float DrivingForce)
{
	TotalForcePerFrame += DrivingForce;
}