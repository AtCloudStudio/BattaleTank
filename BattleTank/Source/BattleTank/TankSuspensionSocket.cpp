// Copyright RyanXu @CloudStudio

#include "TankSuspensionSocket.h"
#include "Kismet\GameplayStatics.h"

UTankSuspensionSocket::UTankSuspensionSocket()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankSuspensionSocket::BeginPlay()
{
	Super::BeginPlay();

	auto SuspensionSystemSocket = GetWorld()->
		SpawnActorDeferred<AActor>(SuspensionSystem, GetComponentTransform());

	if (!SuspensionSystemSocket)
	{
		return;
	}

	SuspensionSystemSocket->AttachToComponent(
		this, FAttachmentTransformRules::KeepWorldTransform);
	UGameplayStatics::FinishSpawningActor(
		SuspensionSystemSocket, GetComponentTransform());
}

void UTankSuspensionSocket::TickComponent(float DeltaTime, 
	ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}