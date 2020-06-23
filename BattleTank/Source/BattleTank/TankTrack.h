// Copyright RyanXu @CloudStudio

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

//Used to set maximum driving force, and to apply forces to the tank
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	//Set tank throttle between -1 and 1
	UFUNCTION(BlueprintCallable, Category = Input)
	void SetThrottle(float Throttle);

	//Max force per track in Newtons *Forece = Mass * Accelleration
	UPROPERTY(EditDefaultsOnly)
	float TrackMaxForce = 80000000.0f;//Assume 40 tonne tank, and 1g accelleration
};