// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Pickup.generated.h"

/**
 * 
 */
UCLASS()
class ROLLERBALL_API APickup : public AActor
{
	GENERATED_UCLASS_BODY()

	/** True when the pickup is able to be picked up, false if something deactivates it*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = pickup)
	bool bIsActive;

	/** Simple collision primitive to use as the root component*/
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = pickup)
	TSubobjectPtr<USphereComponent> BaseCollisionComponent;

	/** StaticMeshComponent to represent the pickup in the level*/
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = pickup)
	TSubobjectPtr<UStaticMeshComponent> PickupMesh;

	/** Function to call when pickup is collected*/
	UFUNCTION(BlueprintNativeEvent)
	void OnPickedUp();
};
