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

	void AddDrivingForce(float ForceMagnitude);

private:	
	void SetupPhysicsConstraint();

	UFUNCTION()
	void OnHit(
		UPrimitiveComponent* HitComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComponent,
		FVector NormalImpulse,
		const FHitResult& Hit);

	UPROPERTY(VisibleAnyWhere, Category = "Components")
	UPhysicsConstraintComponent* TankAxleSpring = nullptr;

	UPROPERTY(VisibleAnyWhere, Category = "Components")
	UPhysicsConstraintComponent* AxleWheelSpring = nullptr;

	UPROPERTY(VisibleAnyWhere, Category = "Components")
	USphereComponent* WheelAxle = nullptr;

	UPROPERTY(VisibleAnyWhere, Category = "Components")
	USphereComponent* Wheel = nullptr;

	float TotalForcePerFrame = 0.0f;
};