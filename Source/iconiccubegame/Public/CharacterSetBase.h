// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CharacterSetBase.generated.h"

/**
 * 
 */
UCLASS()
class ICONICCUBEGAME_API UCharacterSetBase : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	UFUNCTION(BlueprintCallable, Category = "Character")
	static void CharacterSetBase(ACharacter* Character, UPrimitiveComponent* Primitive, bool Reset);
	UFUNCTION(BlueprintCallable, Category = "Character")
	static UPrimitiveComponent CharacterGetBase(ACharacter* Character);
};
