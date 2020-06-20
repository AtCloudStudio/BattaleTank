// Copyright RyanXu @CloudStudio

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Tank.h"
#include "Engine/World.h"
#include "PlayerTankController.generated.h"

UCLASS()
class BATTLETANK_API APlayerTankController : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	ATank* GetControlledTank() const;
	//move barrel to aim where crosshair intersects the world
	FVector GetHitLocation();
	bool GetSightRayHitLocation() const;
	void AimTowardsCrosshair();
};