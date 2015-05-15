// Fill out your copyright notice in the Description page of Project Settings.

#include "RollerBall.h"
#include "pickupMain.h"


ApickupMain::ApickupMain(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	
}

void ApickupMain::onPickupImplementation()
{
	// Call parent implementation on OnPickedUp first.
	Super::OnPickedUp_Implementation();
	// Destroy the object
	Destroy();
}
