// Fill out your copyright notice in the Description page of Project Settings.

#include "Reducers.h"
#include "Actions.h"
#include "State.h"

const UTodoStateArray* TodosReducer(const UTodoStateArray* State, const UAction* Action)
{
	if (!State)
	{
		/* For test
		TArray<UTodoState*> NewArray;

		UTodoState* TodoState = NewObject<UTodoState>();
		TodoState->Id = 100;
		TodoState->Text = FText::FromString("Apple");
		TodoState->bCompleted = true;
		NewArray.Add(TodoState);

		TodoState = NewObject<UTodoState>();
		TodoState->Id = 101;
		TodoState->Text = FText::FromString("Orange");
		TodoState->bCompleted = false;
		NewArray.Add(TodoState);

		UTodoStateArray* NewState = NewObject<UTodoStateArray>();
		NewState->Init(MoveTemp(NewArray));
		return NewState;
		*/
		return NewObject<UTodoStateArray>();
	}

	switch (Action->GetType()) {
	case EActionType::ADD_TODO:
	{
		const UAddTodoAction* AddTodoAction = Action->CastToAddTodoAction();

		TArray<UTodoState*> NewArray;
		NewArray = State->GetArray(); // Shallow Copy

		UTodoState* TodoState = NewObject<UTodoState>();
		TodoState->Id = AddTodoAction->Id;
		TodoState->Text = AddTodoAction->Text;
		TodoState->bCompleted = false;
		NewArray.Add(TodoState);

		UTodoStateArray* NewState = NewObject<UTodoStateArray>();
		NewState->Init(MoveTemp(NewArray));
		return NewState;
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

		UTodoStateArray* NewState = NewObject<UTodoStateArray>();
		NewState->Init(MoveTemp(NewArray));
		return NewState;
	}
	default:
		return State;
	}
}

const UStateString* VisibilityFilterReducer(const UStateString* State, const UAction* Action)
{
	if (!State)
	{
		UStateString* NewState = NewObject<UStateString>();
		NewState->Init(TEXT("SHOW_ALL"));
		return NewState;
	}

	switch (Action->GetType()) {
	case EActionType::SET_VISIBILITY_FILTER:
	{
		UStateString* NewState = NewObject<UStateString>();
		NewState->Init(*Action->CastToSetVisibilityFilterAction()->Filter);
		return NewState;
	}
	default:
		return State;
	}
}
