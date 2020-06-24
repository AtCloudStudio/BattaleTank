// Copyright RyanXu @CloudStudio

#pragma once

#include "CoreMinimal.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "PlayerTankController.generated.h"

class UTankAimingComponent;

// Responsible for player aiming and camera control
UCLASS()
class BATTLETANK_API APlayerTankController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void FindAimingComponent(UTankAimingComponent* AimingComponentReference);

public:
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditDefaultsOnly) float CrosshairLocationX = 0.5f;
	UPROPERTY(EditDefaultsOnly) float CrosshairLocationY = 0.333333;
	UPROPERTY(EditDefaultsOnly) float LineTraceRange = 1000000.0f;

	bool GetSightRayHitLocation(FVector& HitLocation) const;

	//move barrel to aim where crosshair intersects the world
	void AimTowardsCrosshair();
};