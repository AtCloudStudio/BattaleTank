// Copyright RyanXu @CloudStudio

#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::InitializeTracks(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::MoveForward(float Throw)
{
	if (!ensure(LeftTrack) || !ensure(RightTrack)) return;
	
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::TurnRight(float Throw)
{
	if (!ensure(LeftTrack) || !ensure(RightTrack)) return;

	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
}

void UTankMovementComponent::RequestDirectMove
	(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	auto TankForwardDirection = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto AIForwardIntention = MoveVelocity.GetSafeNormal();
	auto ForwardThrow = FVector::DotProduct(TankForwardDirection, AIForwardIntention);
	auto RightThrow = FVector::CrossProduct(TankForwardDirection, AIForwardIntention).Z;

	MoveForward(ForwardThrow);
	TurnRight(RightThrow);
}