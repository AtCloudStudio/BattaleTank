// Copyright RyanXu @CloudStudio

#include "TankTrack.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();
	TankBody = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::OnHit(
	UPrimitiveComponent* HitComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComponent,
	FVector NormalImpulse,
	const FHitResult& Hit)
{
	DriveTrack();
	SidewaySlippageCorrection();
	CurrentThrottle = 0.0f;
}

void UTankTrack::DriveTrack()
{
	if (!ensure(TankBody))
	{
		return;
	}

	TankBody->AddForceAtLocation(
		GetForwardVector() * CurrentThrottle * TrackMaxForce,
		GetComponentLocation());
}

void UTankTrack::SidewaySlippageCorrection()
{
	if (!ensure(TankBody))
	{
		return;
	}

	//Calculate the slippage speed
	//Calculate the required acceleration per frame to correct
	//Calculate corrected sideways force (Force = mass * acceleration)
	//Note that tank has 2 tracks
	//apply correction force
	auto SlippageSpped =
		FVector::DotProduct(GetRightVector(), GetComponentVelocity());
	auto CorrectionAcceleraton =
		SlippageSpped / GetWorld()->GetDeltaSeconds() * GetRightVector() * -1;
	auto CorrectionForce = TankBody->GetMass() * CorrectionAcceleraton / 2;
	TankBody->AddForce(CorrectionForce);
}

void UTankTrack::SetThrottle(float Throttle)
{
	CurrentThrottle =
		FMath::Clamp<float>(CurrentThrottle + Throttle, -1.0f, 1.0f);
}

void UTankTrack::TickComponent(float DeltaTime,
	ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}