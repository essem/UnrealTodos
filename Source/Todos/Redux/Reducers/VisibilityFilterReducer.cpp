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

#if WITH_EDITOR

#define ASSERT_EQUAL(x,y) if ((x)!=(y)) { return false; }

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FVisibilityFilterReducerInitialStateTest, "Redux.VisibilityFilterReducer.InitialState", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool FVisibilityFilterReducerInitialStateTest::RunTest(const FString& Parameters)
{
	const UStateString* NewState = VisibilityFilterReducer(nullptr, nullptr);
	ASSERT_EQUAL(NewState->GetString(), TEXT("SHOW_ALL"));

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FVisibilityFilterReducerSetVisibilityFilterTest, "Redux.VisibilityFilterReducer.SetVisibilityFilter", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool FVisibilityFilterReducerSetVisibilityFilterTest::RunTest(const FString& Parameters)
{
	const UStateString* State = UStateString::Create(TEXT("SHOW_ALL"));
	USetVisibilityFilterAction* Action = NewObject<USetVisibilityFilterAction>();
	Action->Filter = TEXT("SHOW_ACTIVE");

	const UStateString* NewState = VisibilityFilterReducer(State, Action);
	ASSERT_EQUAL(NewState->GetString(), TEXT("SHOW_ACTIVE"));

	return true;
}

#endif
