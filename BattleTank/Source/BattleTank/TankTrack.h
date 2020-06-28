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

private:
	UTankTrack();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
		FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
	void OnHit(
		UPrimitiveComponent* HitComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComponent,
		FVector NormalImpulse,
		const FHitResult& Hit);

	void DriveTrack();
	void SidewaySlippageCorrection();

	UStaticMeshComponent* TankBody = nullptr;
	float CurrentThrottle = 0.0f;

public:
	//Set tank throttle between -1 and 1
	UFUNCTION(BlueprintCallable, Category = "Input")
		void SetThrottle(float Throttle);

	/*Max force per track in Newtons
	Note: Forece = Mass * Accelleration
	Assume 40 tonne tank, 1g accelleration*/
	UPROPERTY(EditDefaultsOnly)
		float TrackMaxForce = 50000000.0f;
};