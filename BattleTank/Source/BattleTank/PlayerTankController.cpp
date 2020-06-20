// Copyright RyanXu @CloudStudio

#include "PlayerTankController.h"

void APlayerTankController::BeginPlay()
{
	Super::BeginPlay();

	if (!GetControlledTank())
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing PlayerTankController!"), 
			*GetControlledTank()->GetName());
	}
}

void APlayerTankController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
	UE_LOG(LogTemp, Warning, TEXT("Tick"));
}

ATank* APlayerTankController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void APlayerTankController::AimTowardsCrosshair()
{
	if (!GetControlledTank())
	{
		return;
	}

	//Get world location if linetrace through crosshair

	//If it hits landscape
		//Tell  controlled tank to aim at this point
	GetSightRayHitLocation();
}

bool APlayerTankController::GetSightRayHitLocation() const
{
	FHitResult Hit;
	FVector Start;
	FVector End;
	ECollisionChannel TraceChannel;
	FCollisionQueryParams Params;
	FCollisionResponseParams ResponseParam;

	if (LineTraceSingleByChannel(
		Hit, 
		Start,
		End,
		TraceChannel,
		Params,
		ResponseParam))
	{
		return true;
	}
	else
	{
		return false;
	}
}

FVector APlayerTankController::GetHitLocation()
{
	FVector HitLocation;

	return HitLocation;
}