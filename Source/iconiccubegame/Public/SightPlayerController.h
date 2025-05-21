// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GenericTeamAgentInterface.h"
#include "SightPlayerController.generated.h"
/**
 * 
 */

class APlayerControllerTeam;

UCLASS()
class ICONICCUBEGAME_API ASightPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ASightPlayerController();


	
protected:
	//Custom UI Nav Based on Mapping
	virtual void SetupInputComponent() override;
	void UINavUp();
	void UINavDown();
	void UINavLeft();
	void UINavRight();
	void UINavConfirm();
	void UINavCancel();
	

private:
	// Implement The Generic Team Interface 
	FGenericTeamId TeamId;
	FGenericTeamId GetGenericTeamId() const;
};



