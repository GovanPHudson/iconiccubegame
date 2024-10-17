// Fill out your copyright notice in the Description page of Project Settings.


#include "SightPlayerController.h"

ASightPlayerController::ASightPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
	TeamId = FGenericTeamId(9);
}

FGenericTeamId ASightPlayerController::GetGenericTeamId() const
{
	return TeamId;
}