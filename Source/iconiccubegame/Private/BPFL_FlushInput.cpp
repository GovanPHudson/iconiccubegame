// Fill out your copyright notice in the Description page of Project Settings.


#include "BPFL_FlushInput.h"

#include "GameFramework/PlayerInput.h"

// ...other includes and code for other things...]

void UBPFL_FlushInput::flushInputs(const APlayerController* PlayerController)
{
	PlayerController->PlayerInput->FlushPressedKeys();
}