// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GetParentClass.generated.h"

/**
 * 
 */
UCLASS()
class ICONICCUBEGAME_API UGetParentClass : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	UFUNCTION(BlueprintCallable, Category = "Class")
	static UClass* GetObjectParentClass(UObject* Object);
	UFUNCTION(BlueprintCallable, Category = "Class")
	static UClass* GetParentClass(UClass* Class);
};
