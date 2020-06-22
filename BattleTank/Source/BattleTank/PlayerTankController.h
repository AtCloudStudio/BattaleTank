// Copyright RyanXu @CloudStudio

#pragma once

#include "CoreMinimal.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "PlayerTankController.generated.h"

class ATank;

UCLASS()
class BATTLETANK_API APlayerTankController : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditDefaultsOnly) float CrosshairLocationX = 0.5f;
	UPROPERTY(EditDefaultsOnly) float CrosshairLocationY = 0.333333;
	UPROPERTY(EditDefaultsOnly) float LineTraceRange = 1000000.0f;

	ATank* GetControlledTank() const;
	bool GetSightRayHitLocation(FVector& HitLocation) const;

	//move barrel to aim where crosshair intersects the world
	void AimTowardsCrosshair();
};