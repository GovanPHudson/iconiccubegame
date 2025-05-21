// Fill out your copyright notice in the Description page of Project Settings.

#include "GameModeBase_CustomSlateNav.h"


AGameModeBase_CustomSlateNav::AGameModeBase_CustomSlateNav() : gameNavigationConfig(MakeShared<FMyGameNavigationConfig>())
{
}

void AGameModeBase_CustomSlateNav::BeginPlay()
{
    Super::BeginPlay();

    // Apply the config to the UI system
    FSlateApplication::Get().SetNavigationConfig(gameNavigationConfig);
}