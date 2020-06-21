// Copyright RyanXu @CloudStudio

#include "TankBarrel.h"

void UTankBarrel::Elevate(float RelativeSpeed)
{
	//Move barrel the right amount per frame
	//Given a max elevation speed and frame time
	auto ElevationChange = 
		RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewElevation = GetRelativeRotation().Pitch + ElevationChange;
	auto Elevation = FMath::Clamp<float>(
		RawNewElevation,
		MinElevationDegrees, 
		MaxElevationDegrees);

	SetRelativeRotation(FRotator(Elevation, 0.0f, 0.0f));
}