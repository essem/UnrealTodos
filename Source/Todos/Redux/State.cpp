// Fill out your copyright notice in the Description page of Project Settings.

#include "State.h"

void UStateString::Init(const TCHAR* InitialString)
{
	String = InitialString;
}

const FString& UStateString::GetString() const
{
	return String;
}

void UTodoStateArray::Init(TArray<UTodoState*>&& InitialArray)
{
	Array = MoveTemp(InitialArray);
}

const TArray<UTodoState*>& UTodoStateArray::GetArray() const
{
	return Array;
}
