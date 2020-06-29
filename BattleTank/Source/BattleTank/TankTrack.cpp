// Copyright RyanXu @CloudStudio

#include "TankTrack.h"
#include "TankSuspensionSystem.h"
#include "TankWheel.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();
}

void UTankTrack::TickComponent(float DeltaTime,
	ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UTankTrack::SetThrottle(float Throttle)
{
	DriveTrack(FMath::Clamp<float>(Throttle, -1.0f, 1.0f));
}

void UTankTrack::DriveTrack(float CurrentThrottle)
{
	for (ATankSuspensionSystem* Wheel : GetWheels())
	{
		Wheel->AddDrivingForce(
			CurrentThrottle * TrackMaxForce / GetWheels().Num());
	}
}

TArray<ATankSuspensionSystem*> UTankTrack::GetWheels() const
{
	TArray<ATankSuspensionSystem*> Wheels;
	TArray<USceneComponent*> Temps;
	GetChildrenComponents(true, Temps);

	for (USceneComponent* Temp : Temps)
	{
		auto Wheel = Cast<UTankWheel>(Temp);

		if (!Wheel) continue;

		auto SuspensionSystem = 
			Cast<ATankSuspensionSystem>(Wheel->GetWheelSocket());

		if (!ensure(SuspensionSystem)) continue;

		Wheels.Add(SuspensionSystem);
	}

	return Wheels;
}