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

FVisibilityFilterReducer::FVisibilityFilterReducer()
{
	Register(EActionType::SET_VISIBILITY_FILTER, SetVisibilityFilter);
}

const UStateString* FVisibilityFilterReducer::GetInitialState() const
{
	return UStateString::Create(TEXT("SHOW_ALL"));
}
