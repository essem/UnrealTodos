// Fill out your copyright notice in the Description page of Project Settings.

#include "MyHUD.h"
#include "JsonObjectConverter.h"
#include "Actions.h"
#include "State.h"
#include "Reducers.h"

void AMyHUD::BeginPlay()
{
	Super::BeginPlay();

	State = NewObject<UAppState>();
	State->Todos = TodosReducer(nullptr, nullptr);
	State->VisibilityFilter = VisibilityFilterReducer(nullptr, nullptr);

	OnStateChanged.Broadcast(State, nullptr);
}

void AMyHUD::Dispatch(const UAction* Action)
{
	check(Action);

	UStruct* StaticStruct = Action->GetStaticStruct();
	FString ClassName = StaticStruct->GetFName().ToString();
	FString ActionJson;
	FJsonObjectConverter::UStructToJsonObjectString(StaticStruct, Action, ActionJson, 0, 0);
	UE_LOG(LogTemp, Display, TEXT("ACTION(%s): %s"), *ClassName, *ActionJson);

	bool bChanged = false;

	TArray<UTodoState*> NewTodos = TodosReducer(&State->Todos, Action);
	bChanged = bChanged || State->Todos != NewTodos;

	FString NewVisibilityFilter = VisibilityFilterReducer(&State->VisibilityFilter, Action);
	bChanged = bChanged || State->VisibilityFilter != NewVisibilityFilter;

	if (bChanged)
	{
		PrevState = State;
		State = NewObject<UAppState>();
		State->Todos = NewTodos;
		State->VisibilityFilter = NewVisibilityFilter;

		OnStateChanged.Broadcast(State, PrevState);
	}

	FString StateJson;
	FJsonObjectConverter::UStructToJsonObjectString(UAppState::StaticClass(), State, StateJson, 0, 0);
	UE_LOG(LogTemp, Display, TEXT("STATE: %s"), *StateJson);
}
