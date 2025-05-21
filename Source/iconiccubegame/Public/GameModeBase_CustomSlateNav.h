// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MyGameNavigationConfig.h"
#include "GameModeBase_CustomSlateNav.generated.h"

/**
 * 
 */
UCLASS()
class ICONICCUBEGAME_API AGameModeBase_CustomSlateNav : public AGameModeBase
{
	GENERATED_BODY()

public:
	AGameModeBase_CustomSlateNav();
	virtual void BeginPlay() override;

private:
	TSharedRef<FMyGameNavigationConfig> gameNavigationConfig;
};
