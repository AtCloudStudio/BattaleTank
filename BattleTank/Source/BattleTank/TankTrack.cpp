// Copyright RyanXu @CloudStudio

#include "TankTrack.h"

void UTankTrack::SetThrottle(float Throttle)
{
	auto Tank = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	Tank->AddForceAtLocation(
		GetForwardVector() * Throttle * TrackMaxForce,
		GetComponentLocation());
}