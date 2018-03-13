// Fill out your copyright notice in the Description page of Project Settings.

#include "Reducers.h"
#include "Actions.h"
#include "State.h"

TArray<UTodoState*> TodosReducer(const TArray<UTodoState*>* State, const UAction* Action)
{
	if (!State)
	{
		//TArray<UTodoState*> NewState;

		//UTodoState* TodoState = NewObject<UTodoState>();
		//TodoState->Id = 100;
		//TodoState->Text = FText::FromString("Apple");
		//TodoState->bCompleted = true;
		//NewState.Add(TodoState);

		//TodoState = NewObject<UTodoState>();
		//TodoState->Id = 101;
		//TodoState->Text = FText::FromString("Orange");
		//TodoState->bCompleted = false;
		//NewState.Add(TodoState);

		//return MoveTemp(NewState);
		return TArray<UTodoState*>();
	}

	switch (Action->GetType()) {
	case EActionType::ADD_TODO:
	{
		const UAddTodoAction* AddTodoAction = Action->CastToAddTodoAction();
		TArray<UTodoState*> NewState;
		NewState = *State;
		UTodoState* TodoState = NewObject<UTodoState>();
		TodoState->Id = AddTodoAction->Id;
		TodoState->Text = AddTodoAction->Text;
		TodoState->bCompleted = false;
		NewState.Add(TodoState);
		return MoveTemp(NewState);
	}
	case EActionType::TOGGLE_TODO:
	{
		const UToggleTodoAction* ToggleTodoAction = Action->CastToToggleTodoAction();
		TArray<UTodoState*> NewState;
		for (UTodoState* TodoState : *State)
		{
			UTodoState* NewTodoState = TodoState;
			if (TodoState->Id == ToggleTodoAction->Id)
			{
				NewTodoState = NewObject<UTodoState>();
				NewTodoState->Id = TodoState->Id;
				NewTodoState->Text = TodoState->Text;
				NewTodoState->bCompleted = !TodoState->bCompleted;
			}
			NewState.Add(NewTodoState);
		}
		return MoveTemp(NewState);
	}
	default:
		return *State;
	}
}

FString VisibilityFilterReducer(const FString* State, const UAction* Action)
{
	if (!State)
	{
		return FString("SHOW_ALL");
	}

	switch (Action->GetType()) {
	case EActionType::SET_VISIBILITY_FILTER:
		return FString(Action->CastToSetVisibilityFilterAction()->Filter);
	default:
		return *State;
	}
}
