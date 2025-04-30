// Fill out your copyright notice in the Description page of Project Settings.


#include "IntToAscii.h"

FString UIntToAscii::IntToAscii(int number)
{
	return FString::Chr(number);
}