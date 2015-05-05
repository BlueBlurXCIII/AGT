// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "RollerBall.h"
#include "RollerBallGameMode.h"
#include "RollerBallBall.h"

ARollerBallGameMode::ARollerBallGameMode(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	// set default pawn class to our ball
	DefaultPawnClass = ARollerBallBall::StaticClass();
}
