// Copyright RyanXu @CloudStudio

#include "TankTrack.h"

void UTankTrack::SetThrottle(float Throttle)
{
	//TODO clamp actual throttle value so player can't over-drive
	//float CurrentThrottle = FMath::Clamp<float>(Throttle, -1.0f, 1.0);
	auto Tank = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	Tank->AddForceAtLocation(
		GetForwardVector() * FMath::Clamp<float>(Throttle, -1.0f, 1.0) * TrackMaxForce,
		GetComponentLocation());
}