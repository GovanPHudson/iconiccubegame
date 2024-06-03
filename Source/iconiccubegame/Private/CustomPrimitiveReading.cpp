// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomPrimitiveReading.h"
#include "Components/PrimitiveComponent.h"

void UCustomPrimitiveReading::GetCustomPrimitiveDataBP(const UPrimitiveComponent *target, TArray<float>& Array)
{
	/*
	TArray<float> Debug;

	Debug = target->GetCustomPrimitiveData().Data;

	for (int i = 0; i < Debug.Num(); i++)
	{
		UE_LOG(LogTemp, Warning, TEXT("%f"), Debug[i]);
	}*/

	Array =	target->GetCustomPrimitiveData().Data;
	
}

void UCustomPrimitiveReading::GetDefaultCustomPrimitiveDataBP(const UPrimitiveComponent *target, TArray<float>& Array)
{
	Array = target->GetDefaultCustomPrimitiveData().Data;
}