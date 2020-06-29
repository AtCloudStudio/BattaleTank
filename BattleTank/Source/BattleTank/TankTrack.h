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

protected:
	virtual void BeginPlay() override;

public:
	//Set tank throttle between -1 and 1
	UFUNCTION(BlueprintCallable, Category = "Input")
	void SetThrottle(float Throttle);

	/*Max force per track in Newtons
	Note: Forece = Mass * Accelleration
	Assume 40 tonne tank, 1g accelleration*/
	UPROPERTY(EditDefaultsOnly)
	float TrackMaxForce = 40000000.0f;

private:
	UTankTrack();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
		FActorComponentTickFunction* ThisTickFunction) override;

	void DriveTrack(float CurrentThrottle);

	TArray<class ATankSuspensionSystem*> GetWheels() const;
};