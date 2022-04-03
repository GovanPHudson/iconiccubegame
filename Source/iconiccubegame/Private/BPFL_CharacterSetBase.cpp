// Fill out your copyright notice in the Description page of Project Settings.


#include "BPFL_CharacterSetBase.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

void UBPFL_CharacterSetBase::CharacterSetBase(ACharacter* Character, UPrimitiveComponent* Primitive, bool Reset)
{
	if (Reset)
	{
		Character->GetCharacterMovement()->SetBase(NULL);
	}
	else
	{
		Character->GetCharacterMovement()->SetBase(Primitive);
	}
}
