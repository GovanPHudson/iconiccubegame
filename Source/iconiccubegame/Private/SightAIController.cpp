// Fill out your copyright notice in the Description page of Project Settings.


#include "SightAIController.h"

ASightAIController::ASightAIController()
{
    SetGenericTeamId(FGenericTeamId(5));
}


ETeamAttitude::Type ASightAIController::GetTeamAttitudeTowards(const AActor& Other) const
{

    if (const APawn* OtherPawn = Cast<APawn>(&Other)) {

        if (const IGenericTeamAgentInterface* TeamAgent = Cast<IGenericTeamAgentInterface>(OtherPawn->GetController()))
        {
            FGenericTeamId OtherTeamID = TeamAgent->GetGenericTeamId();
            switch (OtherTeamID)
            {
            case 0:
            case 1:
            case 2:
            case 3:
            case 4:
                return ETeamAttitude::Neutral;
                break;
            case 5:
                return ETeamAttitude::Friendly;
                break;
            case 6:
            case 7:
            case 8:
            case 9:
            case 10:
                return ETeamAttitude::Hostile;
                break;
            default:
                return ETeamAttitude::Hostile;
                break;
            }
        }


    }


return ETeamAttitude::Hostile;
}