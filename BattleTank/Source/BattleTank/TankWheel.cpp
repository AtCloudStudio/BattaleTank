// Copyright RyanXu @CloudStudio

#include "TankWheel.h"
#include "Kismet\GameplayStatics.h"

UTankWheel::UTankWheel()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankWheel::BeginPlay()
{
	Super::BeginPlay();

	WheelSocket = GetWorld()->
		SpawnActorDeferred<AActor>(SuspensionSystem, GetComponentTransform());

	if (!ensure(WheelSocket)) return;

	WheelSocket->
		AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);
	UGameplayStatics::FinishSpawningActor(WheelSocket, GetComponentTransform());
}

void UTankWheel::TickComponent(float DeltaTime, ELevelTick TickType, 
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

AActor* UTankWheel::GetWheelSocket() const
{
	return WheelSocket;
}