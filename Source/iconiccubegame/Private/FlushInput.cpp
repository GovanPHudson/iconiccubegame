// Fill out your copyright notice in the Description page of Project Settings.


#include "FlushInput.h"
#include "GameFramework/PlayerInput.h"

// ...other includes and code for other things...]

void UFlushInput::flushInputs(const APlayerController* PlayerController)
{
	PlayerController->PlayerInput->FlushPressedKeys();
}