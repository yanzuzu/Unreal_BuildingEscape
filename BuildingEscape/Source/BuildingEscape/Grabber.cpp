// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingEscape.h"
#include "Grabber.h"

#define OUT
// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("Grabber start"));
	
}


// Called every frame
void UGrabber::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	FVector PlayerViewPortPos;
	FRotator PlayerViewPortRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPortPos,
		OUT PlayerViewPortRotation
	);
	//UE_LOG(LogTemp, Warning, TEXT("ViewPoint pos = %s, rotation = %s"),*PlayerViewPortPos.ToString(), *PlayerViewPortRotation.ToString());
	FVector LineTraceEnd = PlayerViewPortPos  +  PlayerViewPortRotation.Vector() * lineTraceLen;
	DrawDebugLine(
		GetWorld(),
		PlayerViewPortPos,
		LineTraceEnd,
		FColor(255, 0, 0),
		false,
		0,
		0,
		10.0f
	);
}

