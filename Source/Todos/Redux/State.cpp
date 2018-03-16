// Fill out your copyright notice in the Description page of Project Settings.

#include "State.h"
#include "JsonObjectConverter.h"

TSharedPtr<FJsonValue> UReduxState::toJSON() const
{
	TSharedRef<FJsonObject> OutJson = MakeShareable(new FJsonObject());
	FJsonObjectConverter::UStructToJsonObject(GetClass(), this, OutJson, 0, 0);
	return MakeShareable(new FJsonValueObject(OutJson));
}

void UStateString::Init(const TCHAR* InitialString)
{
	String = InitialString;
}

const FString& UStateString::GetString() const
{
	return String;
}

TSharedPtr<FJsonValue> UStateString::toJSON() const
{
	return MakeShareable(new FJsonValueString(String));
}

void UTodoStateArray::Init(TArray<UTodoState*>&& InitialArray)
{
	Array = MoveTemp(InitialArray);
}

const TArray<UTodoState*>& UTodoStateArray::GetArray() const
{
	return Array;
}

TSharedPtr<FJsonValue> UTodoStateArray::toJSON() const
{
	TArray<TSharedPtr<FJsonValue>> Out;
	for (UTodoState* TodoState : Array)
	{
		Out.Push(TodoState->toJSON());
	}
	return MakeShareable(new FJsonValueArray(Out));
}
