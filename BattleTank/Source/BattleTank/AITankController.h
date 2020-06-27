// Copyright RyanXu @CloudStudio

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AITankController.generated.h"

UCLASS()
class BATTLETANK_API AAITankController : public AAIController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	//How close can the AI tank get
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float AcceptanceRadius = 10000.0f;
	
public:
	virtual void Tick(float DeltaTime) override;

private:
	virtual void SetPawn(APawn* InPawn) override;

	UFUNCTION()
	void OnControlledTankDeath();

	void DestroyControlledTank();

	float DestroyDelay = 3.0f;
};