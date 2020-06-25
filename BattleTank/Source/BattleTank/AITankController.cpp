// Copyright RyanXu @CloudStudio

#include "AITankController.h"
#include "TankAimingComponent.h"

void AAITankController::BeginPlay()
{
	Super::BeginPlay();
}

void AAITankController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto ControlledTank = GetPawn();
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto AimingComponent =
		GetPawn()->FindComponentByClass<UTankAimingComponent>();

	if (!ensure(PlayerTank) || !ensure(ControlledTank || !ensure(AimingComponent)))
	{
		return;
	}

	MoveToActor(PlayerTank, AcceptanceRadius);
	AimingComponent->AimAt(PlayerTank->GetActorLocation());

	if (AimingComponent->GetAimingState() == EAimingState::Locked)
	{
		AimingComponent->Fire();
	}
}