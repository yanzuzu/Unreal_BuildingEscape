// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingEscape.h"
#include "OpenDoor.h"
#include "GameFramework/Actor.h"

#define OUT

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	SelfActorObj = GetOwner();
}

void UOpenDoor::OpenDoor()
{
	SelfActorObj->SetActorRotation(FRotator(0, OpenAngle, 0));
}

void UOpenDoor::CloseDoor()
{
	SelfActorObj->SetActorRotation(FRotator(0, 0, 0));
}


// Called every frame
void UOpenDoor::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	if (GetOverlapActorsMass() > OpenDoorMassThres)
	{
		OpenDoor();
		LastOpenDoorTime = GetWorld()->GetTimeSeconds();
	}

	if (GetWorld()->GetTimeSeconds() - LastOpenDoorTime > CloseDoorTime)
	{
		CloseDoor();
	}
}

float UOpenDoor::GetOverlapActorsMass()
{
	TArray<AActor*> overlapActors;
	PressurePlate->GetOverlappingActors(OUT overlapActors);

	float totalMass = 0;
	for (auto* actors : overlapActors)
	{
		UPrimitiveComponent* primitiveObj = actors->FindComponentByClass<UPrimitiveComponent>();
		if (primitiveObj != nullptr)
		{
			float mass = primitiveObj->GetMass();
			totalMass += mass;
		}
	}
	return totalMass;
}

