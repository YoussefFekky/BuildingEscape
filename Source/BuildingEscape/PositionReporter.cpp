// Fill out your copyright notice in the Description page of Project Settings.

#include "PositionReporter.h"
#include "GameFramework/Actor.h"


// Sets default values for this component's properties
UPositionReporter::UPositionReporter()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UPositionReporter::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("%s's position: X: %.2f, Y: %.2f, Z: %.2f"), *GetOwner()->GetName(), GetOwner()->GetActorLocation().GetComponentForAxis(EAxis::X), GetOwner()->GetActorLocation().GetComponentForAxis(EAxis::Y), GetOwner()->GetActorLocation().GetComponentForAxis(EAxis::Z));
	
	
}


// Called every frame
void UPositionReporter::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

