// Copyright RyanXu @CloudStudio

#include "PlayerTankController.h"
#include "TankAimingComponent.h"
#include "Tank.h"
#include "Engine/World.h"

void APlayerTankController::BeginPlay()
{
	Super::BeginPlay();

	auto AimingComponent = 
		GetPawn()->FindComponentByClass<UTankAimingComponent>();

	if (!ensure(AimingComponent))
	{
		return;
	}

	FindAimingComponent(AimingComponent);
}

void APlayerTankController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);

	if (InPawn)
	{
		auto PlayerTank = Cast<ATank>(InPawn);

		if (!PlayerTank)
		{
			return;
		}

		PlayerTank->OnDeath.AddUniqueDynamic(
			this, &APlayerTankController::OnPlayerTankDeath);
	}
}

void APlayerTankController::OnPlayerTankDeath()
{
	StartSpectatingOnly();

	//FTimerHandle OUTTimer;
	//GetWorld()->GetTimerManager().SetTimer(OUTTimer, this,
	//	&APlayerTankController::DestroyPlayerTank, DestroyDelay, false);
}

void APlayerTankController::DestroyPlayerTank()
{
	//GetPawn()->Destroy();	//TODO bug
}

void APlayerTankController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

void APlayerTankController::AimTowardsCrosshair()
{
	if (!GetPawn())
	{
		return;
	}

	auto AimingComponent =
		GetPawn()->FindComponentByClass<UTankAimingComponent>();

	if (!ensure(AimingComponent))
	{
		return;
	}

	FVector HitLocation;

	if (GetSightRayHitLocation(HitLocation))
	{
		//If hits any visible actor, tell controlled tank to aim at this location
		AimingComponent->AimAt(HitLocation);
	}
}

//Get world location of linetrace through crosshair, true if hits landscape
bool APlayerTankController::GetSightRayHitLocation(FVector& HitLocation) const
{
	int32 ViewportSizeX;
	int32 ViewportSizeY;

	FVector CameraLocation = PlayerCameraManager->GetCameraLocation();
	FVector CameraDirection;
	FVector LineTraceEnd;

	FRotator CameraRotation = PlayerCameraManager->GetCameraRotation();

	FHitResult HitResult;

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
		ECC_Camera))
	{
		//Set HitLocation
		HitLocation = HitResult.Location;

		return true;
	}
	else
	{
		return false;
	}
} 