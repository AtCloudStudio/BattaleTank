// Copyright RyanXu @CloudStudio

#pragma once

#include "CoreMinimal.h"
//#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	//-1 is max downward speed, and +1 is max up movement speed
	void Elevate(float RelativeSpeed);

private:
	UPROPERTY(EditAnyWhere, Category = Setup)
		float MaxDegreesPerSecond = 5.0f;	//TODO give sensible default value
	UPROPERTY(EditAnyWhere, Category = Setup)
		float MaxElevationDegrees = 35.0f;
	UPROPERTY(EditAnyWhere, Category = Setup)
		float MinElevationDegrees = 0.0f;
};