// Copyright RyanXu @CloudStudio

#include "AITankController.h"
#include "Tank.h"
#include "TankAimingComponent.h"

void AAITankController::BeginPlay()
{
	Super::BeginPlay();
	AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if (!ensure(PlayerTank) || !ensure(AimingComponent)) return;
}

void AAITankController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!PlayerTank || !GetPawn() || !AimingComponent) return;

	AimingComponent->AimAt(PlayerTank->GetActorLocation());

	if (AimingComponent->GetAimingState() == EAimingState::Locked)
	{
		AimingComponent->Fire();
	}
	else
	{
		MoveToActor(PlayerTank, AcceptanceRadius);
	}
}

void AAITankController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);

	if (InPawn)
	{
		auto PossessedTank = Cast<ATank>(InPawn);

		if (!PossessedTank) return;

		//Subscribe local function to the tank's death event
		PossessedTank->OnDeath.AddUniqueDynamic(
			this, &AAITankController::OnControlledTankDeath);
	}
}

void AAITankController::OnControlledTankDeath()
{
	if (!GetPawn()) return;

	GetPawn()->DetachFromControllerPendingDestroy();
	//TODO Really destroy AI tank
}