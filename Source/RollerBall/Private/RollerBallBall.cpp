// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "RollerBall.h"
#include "RollerBallBall.h"
//#include "SpeedPickup.h"

ARollerBallBall::ARollerBallBall(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> BallMesh(TEXT("/Game/Meshes/BallMesh.BallMesh"));

	//Create pickup collection volume
	CollectionSphere = PCIP.CreateDefaultSubobject<USphereComponent>(this, TEXT("CollectionSphere"));
	CollectionSphere->AttachTo(RootComponent);
	CollectionSphere->SetSphereRadius(200.f);


	// Create mesh component for the ball
	Ball = PCIP.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("Ball0"));
	Ball->SetStaticMesh(BallMesh.Object);
	Ball->BodyInstance.SetCollisionProfileName(UCollisionProfile::PhysicsActor_ProfileName);
	Ball->SetSimulatePhysics(true);
	Ball->SetAngularDamping(0.9f);
	Ball->SetLinearDamping(0.1f);
	Ball->BodyInstance.MassScale = 2.f;
	Ball->SetNotifyRigidBodyCollision(true);
	RootComponent = Ball;

	// Create a camera boom attached to the root (ball)
	SpringArm = PCIP.CreateDefaultSubobject<USpringArmComponent>(this, TEXT("SpringArm0"));
	SpringArm->AttachTo(RootComponent);
	SpringArm->bDoCollisionTest = false;
	SpringArm->bAbsoluteRotation = true; // Rotation of the ball should not affect rotation of boom
	SpringArm->RelativeRotation = FRotator(-45.f, 0.f, 0.f);
	SpringArm->TargetArmLength = 1200.f;
	SpringArm->bEnableCameraLag = true;
	SpringArm->CameraLagSpeed = 3.f;

	// Create a camera and attach to boom
	Camera = PCIP.CreateDefaultSubobject<UCameraComponent>(this, TEXT("Camera0"));
	Camera->AttachTo(SpringArm, USpringArmComponent::SocketName);
	Camera->bUseControllerViewRotation = true; // We don't want the controller rotating the camera

	// Set up forces
	RollTorque = 100.f;
	JumpImpulse = 1500000.f;
	bCanJump = true; // Start being able to jump
}


void ARollerBallBall::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	// set up gameplay key bindings
	InputComponent->BindAxis("MoveRight", this, &ARollerBallBall::MoveRight);
	InputComponent->BindAxis("MoveForward", this, &ARollerBallBall::MoveForward);

	InputComponent->BindAction("Jump", IE_Pressed, this, &ARollerBallBall::Jump);
}

void ARollerBallBall::MoveRight(float Val)
{
	const FVector Torque = FVector(-1.f * Val * RollTorque, 0.f, 0.f);
	Ball->AddTorque(Torque);
}

void ARollerBallBall::MoveForward(float Val)
{
	const FVector Torque = FVector(0.f, Val * RollTorque, 0.f);
	Ball->AddTorque(Torque);	
}

void ARollerBallBall::Jump()
{
	if(bCanJump)
	{
		const FVector Impulse = FVector(0.f, 0.f, JumpImpulse);
		Ball->AddImpulse(Impulse);
		bCanJump = false;
	}
}

void ARollerBallBall::ReceiveHit(class UPrimitiveComponent* MyComp, class AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::ReceiveHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);

	bCanJump = true;
}


/*void ARollerBallBall::OnPickedUp_Implementation()
{
	//float Val;
	//Get all overlapping Actors and store them in a CollectedActors  array
	TArray<AActor*> CollectedActors;
	CollectionSphere->GetOverlappingActors(CollectedActors);
	Super::OnActorBeginOverlap;
	//For each actor collected
	for (int32 iCollected = 0; iCollected < CollectedActors.Num(); ++iCollected)
	{
		//cast the collected actor to ASpeedPickup
		ASpeedPickup* const sP = Cast<ASpeedPickup>(CollectedActors[iCollected]);

		//if the cast is successful, and pickup is valid and active
		if (sP && !sP->IsPendingKill() && sP->bIsActive)
		{
			//const FVector Torque = FVector(0.f, Val * RollTorque, 0.f);
			//Ball->AddTorque(Torque + 1000000);
			//Call the battery's OnPickedUp function
			sP->OnPickedUp();
			//Deactivate the battery
			sP->bIsActive = false;
			//ASpeedPickup* destroy();
		}
	}
}*/