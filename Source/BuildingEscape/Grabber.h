// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Components/InputComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	void SetPhysicsHandle();
	void GetInput();
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	FVector GetPlayerReach() const;
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	const float Reach = 100.f;
	UPhysicsHandleComponent* PhysicsHandle = nullptr;
	UInputComponent* Input = nullptr;
	
	FHitResult GetHit() const;

	// Allows player to grab a physics component
	void Grab();
	// Allows player to release a physics component
	void Release();

};
