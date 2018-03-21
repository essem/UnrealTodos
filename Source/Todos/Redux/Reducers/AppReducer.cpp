// Fill out your copyright notice in the Description page of Project Settings.

#include "AppReducer.h"
#include "../Actions.h"
#include "../State.h"

const UAppState* FAppReducer::GetInitialState() const
{
	UAppState* NewState = NewObject<UAppState>();
	NewState->Todos = TodosReducer.GetInitialState();
	NewState->VisibilityFilter = VisibilityFilterReducer.GetInitialState();
	return NewState;
}

const UAppState* FAppReducer::Reduce(const UAppState* State, const UAction* Action) const
{
	check(State && Action);

	bool bChanged = false;

	const UTodoStateArray* NewTodos = TodosReducer.Reduce(State->Todos, Action);
	bChanged = bChanged || State->Todos != NewTodos;

	const UStateString* NewVisibilityFilter = VisibilityFilterReducer.Reduce(State->VisibilityFilter, Action);
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
