// Fill out your copyright notice in the Description page of Project Settings.

#include "State.h"
#include "JsonObjectConverter.h"

// UReduxState ===========================================================================

TSharedPtr<FJsonValue> UReduxState::ToJson() const
{
	FJsonObjectConverter::CustomExportCallback ExportCb;
	ExportCb.BindLambda([](UProperty* Property, const void* Value) -> TSharedPtr<FJsonValue>
	{
		if (UObjectProperty* ObjectProperty = Cast<UObjectProperty>(Property))
		{
			UObject* Object = ObjectProperty->GetObjectPropertyValue(Value);
			UReduxState* State = Cast<UReduxState>(Object);
			if (State)
			{
				return State->ToJson();
			}
			TSharedRef<FJsonObject> OutJson = MakeShareable(new FJsonObject());
			FJsonObjectConverter::UStructToJsonObject(Object->GetClass(), Object, OutJson, 0, 0);
			return MakeShareable(new FJsonValueObject(OutJson));
		}

		return TSharedPtr<FJsonValue>();
	});

	TSharedRef<FJsonObject> OutJson = MakeShareable(new FJsonObject());
	FJsonObjectConverter::UStructToJsonObject(GetClass(), this, OutJson, 0, 0, &ExportCb);
	return MakeShareable(new FJsonValueObject(OutJson));
}

// UStateString ==========================================================================

void UStateString::Init(FString&& InitialString)
{
	String = MoveTemp(InitialString);
}

UStateString* UStateString::Create(const TCHAR* InitialString)
{
	UStateString* StateString = NewObject<UStateString>();
	StateString->Init(FString(InitialString));
	return StateString;
}

UStateString* UStateString::Create(const FString& InitialString)
{
	UStateString* StateString = NewObject<UStateString>();
	StateString->Init(CopyTemp(InitialString));
	return StateString;
}

UStateString* UStateString::Create(FString&& InitialString)
{
	UStateString* StateString = NewObject<UStateString>();
	StateString->Init(MoveTemp(InitialString));
	return StateString;
}

const FString& UStateString::GetString() const
{
	return String;
}

TSharedPtr<FJsonValue> UStateString::ToJson() const
{
	return MakeShareable(new FJsonValueString(String));
}

// UStateText ============================================================================

void UStateText::Init(FText&& InitialText)
{
	Text = MoveTemp(InitialText);
}

UStateText* UStateText::Create(const FText& InitialText)
{
	UStateText* StateText = NewObject<UStateText>();
	StateText->Init(CopyTemp(InitialText));
	return StateText;
}

UStateText* UStateText::Create(FText&& InitialText)
{
	UStateText* StateText = NewObject<UStateText>();
	StateText->Init(MoveTemp(InitialText));
	return StateText;
}

const FText& UStateText::GetText() const
{
	return Text;
}

TSharedPtr<FJsonValue> UStateText::ToJson() const
{
	return MakeShareable(new FJsonValueString(Text.ToString()));
}

// UTodoStateArray =======================================================================

void UTodoStateArray::Init(TArray<UTodoState*>&& InitialArray)
{
	Array = MoveTemp(InitialArray);
}

UTodoStateArray* UTodoStateArray::Create(TArray<UTodoState*>&& InitialArray)
{
	UTodoStateArray* StateArray = NewObject<UTodoStateArray>();
	StateArray->Init(MoveTemp(InitialArray));
	return StateArray;
}

const TArray<UTodoState*>& UTodoStateArray::GetArray() const
{
	return Array;
}

TSharedPtr<FJsonValue> UTodoStateArray::ToJson() const
{
	TArray<TSharedPtr<FJsonValue>> Out;
	for (UTodoState* TodoState : Array)
	{
		Out.Push(TodoState->ToJson());
	}
	return MakeShareable(new FJsonValueArray(Out));
}
