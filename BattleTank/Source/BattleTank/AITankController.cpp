// Copyright RyanXu @CloudStudio

#include "AITankController.h"
#include "Tank.h"
#include "TankAimingComponent.h"

void AAITankController::BeginPlay()
{
	Super::BeginPlay();
}

void AAITankController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);

	if (InPawn)
	{
		auto ControlledTank = Cast<ATank>(InPawn);

		if (!ControlledTank)
		{
			return;
		}

		//Subscribe local function to the tank's death event
		ControlledTank->OnDeath.AddUniqueDynamic(
			this, &AAITankController::OnControlledTankDeath);
	}
}

void AAITankController::OnControlledTankDeath()
{
	if (!GetPawn())
	{
		return;
	}

	GetPawn()->DetachFromControllerPendingDestroy();
	FTimerHandle OUTTimer;
	GetWorld()->GetTimerManager().SetTimer(OUTTimer, this,
		&AAITankController::DestroyControlledTank, DestroyDelay, false);
}

void AAITankController::DestroyControlledTank()
{
	GetPawn()->Destroy();	//TODO Bug
}

void AAITankController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto ControlledTank = GetPawn();
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto AimingComponent =
		GetPawn()->FindComponentByClass<UTankAimingComponent>();

	if (!PlayerTank || !ensure(ControlledTank) || !ensure(AimingComponent))
	{
		return;
	}

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