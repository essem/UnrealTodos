// Fill out your copyright notice in the Description page of Project Settings.

#include "Store.h"
#include "Todos.h"
#include "JsonObjectConverter.h"
#include "Actions.h"
#include "State.h"
#include "Reducers.h"

UStore::UStore()
	: CurrentStateIndex(-1)
{
}

void UStore::Init()
{
	States.Add(AppReducer(nullptr, nullptr));
	CurrentStateIndex = 0;

	DumpState(*States[CurrentStateIndex]);
}

const UAppState& UStore::GetAppState() const
{
	return *States[CurrentStateIndex];
}

void UStore::Dispatch(const UAction* Action)
{
	check(Action);

	DumpAction(*Action);

	const UAppState* CurState = States[CurrentStateIndex];
	const UAppState* NewState = AppReducer(CurState, Action);
	if (NewState != CurState)
	{
		if (States.Num() > CurrentStateIndex + 1)
		{
			States.SetNum(CurrentStateIndex + 1);
		}

		States.Add(NewState);
		++CurrentStateIndex;

		DumpState(*NewState);
		OnStateChanged.Broadcast(NewState, CurState);
	}
}

bool UStore::CanUndo() const
{
	return CurrentStateIndex > 0;
}

void UStore::Undo()
{
	if (CanUndo())
	{
		const UAppState* CurState = States[CurrentStateIndex];
		--CurrentStateIndex;
		const UAppState* NewState = States[CurrentStateIndex];

		DumpState(*NewState);
		OnStateChanged.Broadcast(NewState, CurState);
	}
}

bool UStore::CanRedo() const
{
	return CurrentStateIndex < States.Num() - 1;
}

void UStore::Redo()
{
	if (CanRedo())
	{
		const UAppState* CurState = States[CurrentStateIndex];
		++CurrentStateIndex;
		const UAppState* NewState = States[CurrentStateIndex];

		DumpState(*NewState);
		OnStateChanged.Broadcast(NewState, CurState);
	}
}


void UStore::DumpAction(const UAction& Action) const
{
	UClass* ActionClass = Action.GetClass();
	FString ClassName = ActionClass->GetFName().ToString();
	FString ActionJson;
	FJsonObjectConverter::UStructToJsonObjectString(ActionClass, &Action, ActionJson, 0, 0);
	UE_LOG(Redux, Display, TEXT("=== ACTION: %s ===\n%s"), *ClassName, *ActionJson);
}

void UStore::DumpState(const UAppState& State) const
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
				return State->toJSON();
			}
			TSharedRef<FJsonObject> OutJson = MakeShareable(new FJsonObject());
			FJsonObjectConverter::UStructToJsonObject(Object->GetClass(), Object, OutJson, 0, 0);
			return MakeShareable(new FJsonValueObject(OutJson));
		}

		return TSharedPtr<FJsonValue>();
	});

	FString StateJson;
	FJsonObjectConverter::UStructToJsonObjectString(UAppState::StaticClass(), &State, StateJson, 0, 0, 0, &ExportCb, true);
	UE_LOG(Redux, Display, TEXT("=== STATE ===\n%s"), *StateJson);
}
