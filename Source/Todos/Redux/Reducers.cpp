// Fill out your copyright notice in the Description page of Project Settings.

#include "Reducers.h"
#include "Actions.h"
#include "State.h"

const UAppState* AppReducer(const UAppState* State, const UAction* Action)
{
	if (!State)
	{
		UAppState* NewState = NewObject<UAppState>();
		NewState->Todos = TodosReducer(nullptr, nullptr);
		NewState->VisibilityFilter = VisibilityFilterReducer(nullptr, nullptr);
		return NewState;
	}

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

const UTodoStateArray* TodosReducer(const UTodoStateArray* State, const UAction* Action)
{
	if (!State)
	{
		// Uncomment below to test

		//TArray<UTodoState*> NewArray;

		//UTodoState* TodoState = NewObject<UTodoState>();
		//TodoState->Id = 100;
		//TodoState->Text = UStateText::Create(FText::FromString("Apple"));
		//TodoState->bCompleted = true;
		//NewArray.Add(TodoState);

		//TodoState = NewObject<UTodoState>();
		//TodoState->Id = 101;
		//TodoState->Text = UStateText::Create(FText::FromString("Orange"));
		//TodoState->bCompleted = false;
		//NewArray.Add(TodoState);

		//return UTodoStateArray::Create(MoveTemp(NewArray));

		return NewObject<UTodoStateArray>();
	}

	switch (Action->GetType()) {
	case EActionType::ADD_TODO:
	{
		const UAddTodoAction* AddTodoAction = Action->CastToAddTodoAction();

		TArray<UTodoState*> NewArray;
		NewArray = State->GetArray(); // Shallow Copy

		UTodoState* NewTodoState = NewObject<UTodoState>();
		NewTodoState->Id = AddTodoAction->Id;
		NewTodoState->Text = UStateText::Create(AddTodoAction->Text);
		NewTodoState->bCompleted = false;
		NewArray.Add(NewTodoState);

		return UTodoStateArray::Create(MoveTemp(NewArray));
	}
	case EActionType::TOGGLE_TODO:
	{
		const UToggleTodoAction* ToggleTodoAction = Action->CastToToggleTodoAction();

		TArray<UTodoState*> NewArray;
		for (UTodoState* TodoState : State->GetArray())
		{
			UTodoState* NewTodoState = TodoState;
			if (TodoState->Id == ToggleTodoAction->Id)
			{
				NewTodoState = NewObject<UTodoState>();
				NewTodoState->Id = TodoState->Id;
				NewTodoState->Text = TodoState->Text;
				NewTodoState->bCompleted = !TodoState->bCompleted;
			}
			NewArray.Add(NewTodoState);
		}

		return UTodoStateArray::Create(MoveTemp(NewArray));
	}
	default:
		return State;
	}
}

const UStateString* VisibilityFilterReducer(const UStateString* State, const UAction* Action)
{
	if (!State)
	{
		return UStateString::Create(TEXT("SHOW_ALL"));
	}

	switch (Action->GetType()) {
	case EActionType::SET_VISIBILITY_FILTER:
	{
		return UStateString::Create(*Action->CastToSetVisibilityFilterAction()->Filter);
	}
	default:
		return State;
	}
}
