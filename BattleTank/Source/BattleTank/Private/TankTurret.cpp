// Copyright RyanXu @CloudStudio

#include "TankTurret.h"

void UTankTurret::Rotate(float RelativeSpeed)
{
	//Move turret right amount per frame
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed,  -1.0f, 1.0f);
	auto RotationChange =
		RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto Rotation = GetRelativeRotation().Yaw + RotationChange;

	SetRelativeRotation(FRotator(0.0f, Rotation, 0.0f));
}