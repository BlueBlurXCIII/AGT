// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Pickup.h"
#include "pickupMain.generated.h"

/**
 * 
 */
UCLASS()
class ROLLERBALL_API ApickupMain : public APickup
{
	GENERATED_UCLASS_BODY()

	void onPickupImplementation();
	
};
