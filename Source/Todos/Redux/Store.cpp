// Fill out your copyright notice in the Description page of Project Settings.

#include "Store.h"
#include "Todos.h"
#include "JsonObjectConverter.h"
#include "Actions.h"
#include "State.h"
#include "Reducers.h"

void UStore::Init()
{
	State = NewObject<UAppState>();
	State->Todos = TodosReducer(nullptr, nullptr);
	State->VisibilityFilter = VisibilityFilterReducer(nullptr, nullptr);

	DumpState(*State);
}

const UAppState& UStore::GetAppState() const
{
	return *State;
}

void UStore::Dispatch(const UAction* Action)
{
	check(Action);

	DumpAction(*Action);

	// Apply reducers

	bool bChanged = false;

	const UTodoStateArray* NewTodos = TodosReducer(State->Todos, Action);
	bChanged = bChanged || State->Todos != NewTodos;

	const UStateString* NewVisibilityFilter = VisibilityFilterReducer(State->VisibilityFilter, Action);
	bChanged = bChanged || State->VisibilityFilter != NewVisibilityFilter;

	// Fire event if state is changed

	if (bChanged)
	{
		PrevState = State;
		State = NewObject<UAppState>();
		State->Todos = NewTodos;
		State->VisibilityFilter = NewVisibilityFilter;

		DumpState(*State);

		OnStateChanged.Broadcast(State, PrevState);
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
