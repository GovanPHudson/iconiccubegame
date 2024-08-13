// Fill out your copyright notice in the Description page of Project Settings.


#include "GetParentClass.h"

UClass* UGetParentClass::GetObjectParentClass(UObject* Object)
{
    return Object->GetClass()->GetSuperClass();
}

UClass* UGetParentClass::GetParentClass(UClass* Class)
{
    return Class->GetSuperClass();
}