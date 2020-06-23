// Copyright RyanXu @CloudStudio

#include "AITankController.h"
#include "Tank.h"

void AAITankController::BeginPlay()
{
	Super::BeginPlay();

	ControlledTank = Cast<ATank>(GetPawn());
	PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing AITankController!"), 
			*ControlledTank->GetName());
	}
	else if (!PlayerTank)
	{
		UE_LOG(LogTemp, Error,
			TEXT("AITankController can NOT find player tank!"));
	}
}

void AAITankController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!PlayerTank)
	{
		return;
	}

	//Move towards player tank
	MoveToActor(PlayerTank, AcceptanceRadius);

	//Aim towards player tank
	ControlledTank->AimAt(PlayerTank->GetActorLocation());

	//If ready, fire
	ControlledTank->Fire();
}