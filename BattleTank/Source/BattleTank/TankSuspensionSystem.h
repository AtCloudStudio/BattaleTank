// Copyright RyanXu @CloudStudio

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TankSuspensionSystem.generated.h"

class UPhysicsConstraintComponent;
class USphereComponent;

UCLASS()
class BATTLETANK_API ATankSuspensionSystem : public AActor
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	
public:	
	ATankSuspensionSystem();
	virtual void Tick(float DeltaTime) override;

private:	
	UPROPERTY(VisibleAnyWhere, Category = "Components")
	UPhysicsConstraintComponent* TankAxleSpring = nullptr;

	UPROPERTY(VisibleAnyWhere, Category = "Components")
	UPhysicsConstraintComponent* AxleWheelSpring = nullptr;

	UPROPERTY(VisibleAnyWhere, Category = "Components")
	USphereComponent* SuspensionAxle = nullptr;

	UPROPERTY(VisibleAnyWhere, Category = "Components")
	USphereComponent* SuspensionWheel = nullptr;

	void SetupPhysicsConstraint();
};