// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "DrawDebugHelpers.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

FVector UGrabber::GetPlayerReach() const
{
	FVector PlayerLocation;
	FRotator PlayerRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(PlayerLocation, PlayerRotation);
	return PlayerLocation + Reach * PlayerRotation.Vector();
}

FHitResult UGrabber::GetHit() const
{
	FHitResult Hit;
	GetWorld()->LineTraceSingleByObjectType(Hit, 
		GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation(), GetPlayerReach(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		FCollisionQueryParams(FName(), false, GetOwner())
	);
	return Hit;
}

void UGrabber::Grab()
{
	if (PhysicsHandle) {
		FHitResult Hit;
		Hit = GetHit();
		if (Hit.IsValidBlockingHit()) {
			PhysicsHandle->GrabComponent(Hit.GetComponent(), NAME_None, Hit.GetActor()->GetActorLocation(), true);
		}
	}
}

void UGrabber::Release()
{
	if(PhysicsHandle)
		PhysicsHandle->ReleaseComponent();
}

void UGrabber::SetPhysicsHandle()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();

	if (!PhysicsHandle)
		UE_LOG(LogTemp, Error, TEXT("%s is missing its physics handle component!"), *GetOwner()->GetName())
}

void UGrabber::GetInput()
{
	Input = GetOwner()->FindComponentByClass<UInputComponent>();

	if (Input) {
		Input->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		Input->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
	else
		UE_LOG(LogTemp, Error, TEXT("%s is missing its input component!"), *GetOwner()->GetName())
}

// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	
	SetPhysicsHandle();

	GetInput();
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (PhysicsHandle && PhysicsHandle->GrabbedComponent) {
		PhysicsHandle->SetTargetLocation(GetPlayerReach());
	}

}



