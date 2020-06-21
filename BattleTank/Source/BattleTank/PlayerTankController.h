// Copyright RyanXu @CloudStudio

#pragma once

#include "CoreMinimal.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Tank.h"
#include "PlayerTankController.generated.h"

UCLASS()
class BATTLETANK_API APlayerTankController : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnyWhere) float CrosshairLocationX = 0.5f;
	UPROPERTY(EditAnyWhere) float CrosshairLocationY = 0.333333;
	UPROPERTY(EditAnyWhere) float LineTraceRange = 1000000.0f;

	ATank* GetControlledTank() const;
	bool GetSightRayHitLocation(FVector& HitLocation) const;

	//move barrel to aim where crosshair intersects the world
	void AimTowardsCrosshair();
};