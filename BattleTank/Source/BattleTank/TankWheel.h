// Copyright RyanXu @CloudStudio

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "TankWheel.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankWheel : public USceneComponent
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:	
	UTankWheel();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, 
	FActorComponentTickFunction* ThisTickFunction) override;

	AActor* GetWheelSocket() const;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AActor> SuspensionSystem;

	UPROPERTY()
	AActor* WheelSocket = nullptr;
};