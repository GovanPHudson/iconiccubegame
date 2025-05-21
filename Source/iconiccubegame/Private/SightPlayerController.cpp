// Fill out your copyright notice in the Description page of Project Settings.

#include "SightPlayerController.h"
#include "Framework/Application/SlateApplication.h"
#include "InputCoreTypes.h"

ASightPlayerController::ASightPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
	TeamId = FGenericTeamId(9);
}

FGenericTeamId ASightPlayerController::GetGenericTeamId() const
{
	return TeamId;
}

//Custom UI Nav Based on Mapping
void ASightPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	FInputActionBinding& UpBinding		= InputComponent->BindAction("UI_Up"		, IE_Pressed, this, &ASightPlayerController::UINavUp);
	UpBinding.bConsumeInput = false;
	UpBinding.bExecuteWhenPaused = true;

	FInputActionBinding& DownBinding	= InputComponent->BindAction("UI_Down"	, IE_Pressed, this, &ASightPlayerController::UINavDown);
	DownBinding.bConsumeInput = false;
	DownBinding.bExecuteWhenPaused = true;

	FInputActionBinding& LeftBinding	= InputComponent->BindAction("UI_Left"	, IE_Pressed, this, &ASightPlayerController::UINavLeft);
	LeftBinding.bConsumeInput = false;
	LeftBinding.bExecuteWhenPaused = true;

	FInputActionBinding& RightBinding	= InputComponent->BindAction("UI_Right"	, IE_Pressed, this, &ASightPlayerController::UINavRight);
	RightBinding.bConsumeInput = false;
	RightBinding.bExecuteWhenPaused = true;

	FInputActionBinding& ConfirmBinding	= InputComponent->BindAction("UI_Confirm"	, IE_Pressed, this, &ASightPlayerController::UINavConfirm);
	ConfirmBinding.bConsumeInput = false;
	ConfirmBinding.bExecuteWhenPaused = true;

	FInputActionBinding& CancelBinding	= InputComponent->BindAction("UI_Cancel"	, IE_Pressed, this, &ASightPlayerController::UINavCancel);
	CancelBinding.bConsumeInput = false;
	CancelBinding.bExecuteWhenPaused = true;

}

void ASightPlayerController::UINavUp()
{
	FKeyEvent PhantomEvent(EKeys::OculusTouch_Left_Thumbstick_Up	, FModifierKeysState(), 0, false, 0, 0);
	FSlateApplication::Get().ProcessKeyDownEvent(PhantomEvent);
	FSlateApplication::Get().ProcessKeyUpEvent(PhantomEvent);
}
void ASightPlayerController::UINavDown()
{
	FKeyEvent PhantomEvent(EKeys::OculusTouch_Left_Thumbstick_Down	, FModifierKeysState(), 0, false, 0, 0);
	FSlateApplication::Get().ProcessKeyDownEvent(PhantomEvent);
	FSlateApplication::Get().ProcessKeyUpEvent(PhantomEvent);
}
void ASightPlayerController::UINavLeft()
{
	FKeyEvent PhantomEvent(EKeys::OculusTouch_Left_Thumbstick_Left	, FModifierKeysState(), 0, false, 0, 0);
	FSlateApplication::Get().ProcessKeyDownEvent(PhantomEvent);
	FSlateApplication::Get().ProcessKeyUpEvent(PhantomEvent);
}
void ASightPlayerController::UINavRight()
{
	FKeyEvent PhantomEvent(EKeys::OculusTouch_Left_Thumbstick_Right	, FModifierKeysState(), 0, false, 0, 0);
	FSlateApplication::Get().ProcessKeyDownEvent(PhantomEvent);
	FSlateApplication::Get().ProcessKeyUpEvent(PhantomEvent);
}
void ASightPlayerController::UINavConfirm()
{
	FKeyEvent PhantomEvent(EKeys::OculusTouch_Left_Trigger_Click, FModifierKeysState(), 0, false, 0, 0);
	FSlateApplication::Get().ProcessKeyDownEvent(PhantomEvent);
	FSlateApplication::Get().ProcessKeyUpEvent(PhantomEvent); 
}
void ASightPlayerController::UINavCancel()
{
	FKeyEvent PhantomEvent(EKeys::OculusTouch_Right_Trigger_Click, FModifierKeysState(), 0, false, 0, 0);
	FSlateApplication::Get().ProcessKeyDownEvent(PhantomEvent);
	FSlateApplication::Get().ProcessKeyUpEvent(PhantomEvent); 
}

