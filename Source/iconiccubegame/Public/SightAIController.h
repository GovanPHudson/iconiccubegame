// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "GenericTeamAgentInterface.h"
#include "SightAIController.generated.h"

/**
 * 
 */
UCLASS()
class ICONICCUBEGAME_API ASightAIController : public AAIController
{
	GENERATED_BODY()
	ASightAIController();

public:
	// Override this function 
	ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;
};
