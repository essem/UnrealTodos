// Fill out your copyright notice in the Description page of Project Settings.

#include "AppReducer.h"
#include "../Actions.h"
#include "../State.h"
#include "TodosReducer.h"
#include "VisibilityFilterReducer.h"

const UAppState* AppReducer(const UAppState* State, const UAction* Action)
{
	if (!State)
	{
		UAppState* NewState = NewObject<UAppState>();
		NewState->Todos = TodosReducer(nullptr, nullptr);
		NewState->VisibilityFilter = VisibilityFilterReducer(nullptr, nullptr);
		return NewState;
	}

	check(Action);

	bool bChanged = false;

	const UTodoStateArray* NewTodos = TodosReducer(State->Todos, Action);
	bChanged = bChanged || State->Todos != NewTodos;

	const UStateString* NewVisibilityFilter = VisibilityFilterReducer(State->VisibilityFilter, Action);
	bChanged = bChanged || State->VisibilityFilter != NewVisibilityFilter;

	if (!bChanged)
	{
		return State;
	}

	UAppState* NewState = NewObject<UAppState>();
	NewState->Todos = NewTodos;
	NewState->VisibilityFilter = NewVisibilityFilter;
	return NewState;
}
