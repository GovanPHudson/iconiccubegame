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

private:
	// Implement The Generic Team Interface 
	FGenericTeamId TeamId;
	FGenericTeamId GetGenericTeamId() const;
};
