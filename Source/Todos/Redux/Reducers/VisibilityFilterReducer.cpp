// Fill out your copyright notice in the Description page of Project Settings.

#include "VisibilityFilterReducer.h"
#include "../Actions.h"
#include "../State.h"

const UStateString* SetVisibilityFilter(const UStateString* State, const UAction* Action)
{
	const USetVisibilityFilterAction* SetVisibilityFilterAction = Action->CastToSetVisibilityFilterAction();
	check(SetVisibilityFilterAction);

	return UStateString::Create(SetVisibilityFilterAction->Filter);
}

const UStateString* VisibilityFilterReducer(const UStateString* State, const UAction* Action)
{
	if (!State)
	{
		return UStateString::Create(TEXT("SHOW_ALL"));
	}

	switch (Action->GetType())
	{
	case EActionType::SET_VISIBILITY_FILTER: return SetVisibilityFilter(State, Action);
	}

	return State;
}
