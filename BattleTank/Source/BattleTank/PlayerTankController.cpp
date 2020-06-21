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

	FVector HitLocation;

	if (GetSightRayHitLocation(HitLocation))
	{
		//If hits any visible actor, tell controlled tank to aim at this location
		GetControlledTank()->AimAt(HitLocation);
		UE_LOG(LogTemp, Warning, TEXT("Barrel->Elevate() called."));
	}
}
//Get world location of linetrace through crosshair, true if hits landscape
bool APlayerTankController::GetSightRayHitLocation(FVector& HitLocation) const
{
	int32 ViewportSizeX;
	int32 ViewportSizeY;

	FVector CameraLocation = PlayerCameraManager->GetCameraLocation();
	FVector CameraDirection;

	FRotator CameraRotation = PlayerCameraManager->GetCameraRotation();

	FHitResult HitResult;
	FVector LineTraceEnd;
	FCollisionQueryParams LineTraceParams(FName(TEXT("")), false, GetControlledTank());

	//Find crosshair screen position
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto CrosshairLocation = FVector2D(
		ViewportSizeX * CrosshairLocationX, 
		ViewportSizeY * CrosshairLocationY);

	//Deproject crosshair screen position to a world look direction
	DeprojectScreenPositionToWorld(
		CrosshairLocation.X, 
		CrosshairLocation.Y,
		CameraLocation,
		CameraDirection);

	//Get world viewpoint
	GetPlayerViewPoint(CameraLocation, CameraRotation);
	LineTraceEnd = CameraLocation + CameraDirection * LineTraceRange;

	//Line-trace along look direction, and see what it hit (up to max range)
	if (GetWorld()->LineTraceSingleByChannel(
		HitResult,
		CameraLocation,
		LineTraceEnd,
		ECC_Visibility,
		LineTraceParams))
	{
		//Set HitLocation
		HitLocation = HitResult.Location;
		//UE_LOG(LogTemp, Warning, TEXT("Hit result: %s"), *HitResult.GetActor()->GetName());
		return true;
	}
	else
	{
		return false;
	}
} 