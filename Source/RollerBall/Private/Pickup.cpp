// Fill out your copyright notice in the Description page of Project Settings.

#include "RollerBall.h"
#include "Pickup.h"


APickup::APickup(const class FPostConstructInitializeProperties& PCIP)
: Super(PCIP)
{
	// is valid when created
	bIsActive = true;

	//create root SphereComponent to handle the pickup's collision
	BaseCollisionComponent = PCIP.CreateDefaultSubobject<USphereComponent>(this, TEXT("BaseSphereComponent"));

	// set SphereComponent as the root component
	RootComponent = BaseCollisionComponent;

	//Create static mesh component
	PickupMesh = PCIP.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("PickupMesh"));

	//Turn physics on for static mesh
	PickupMesh->SetSimulatePhysics(true);

	//Attach the StaticMeshComponent to root component
	PickupMesh->AttachTo(RootComponent);


}

void APickup::OnPickedUp_Implementation()
{
	//No behavior
}