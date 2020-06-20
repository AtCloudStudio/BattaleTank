// Copyright RyanXu @CloudStudio

#include "AITankController.h"

void AAITankController::BeginPlay()
{
	Super::BeginPlay();

	if (!GetControlledTank())
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing AITankController!"), 
			*GetControlledTank()->GetName());
	}

	if (!GetPlayerTank())
	{
		UE_LOG(LogTemp, Error, 
			TEXT("AITankController can NOT find player tank!"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, 
			TEXT("AITankController has found player: %s!"),
			*GetPlayerTank()->GetName());
	}
}

ATank* AAITankController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* AAITankController::GetPlayerTank() const
{
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (!PlayerTank)
	{
		return nullptr;
	}

	return Cast<ATank>(PlayerTank);
}