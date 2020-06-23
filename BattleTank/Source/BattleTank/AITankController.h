// Copyright RyanXu @CloudStudio

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AITankController.generated.h"

class ATank;

UCLASS()
class BATTLETANK_API AAITankController : public AAIController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	ATank* ControlledTank;
	ATank* PlayerTank;

	//How close can the AI tank get
	float AcceptanceRadius = 3000.0f;	//TODO Check raidus is in cm
};