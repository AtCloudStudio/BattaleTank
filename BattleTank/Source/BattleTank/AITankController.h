// Copyright RyanXu @CloudStudio

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AITankController.generated.h"

UCLASS()
class BATTLETANK_API AAITankController : public AAIController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	//How close can the AI tank get
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float AcceptanceRadius = 100000.0f;
};