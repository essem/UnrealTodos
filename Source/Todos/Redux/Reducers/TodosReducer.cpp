// Fill out your copyright notice in the Description page of Project Settings.

#include "TodosReducer.h"
#include "../Actions.h"
#include "../State.h"

const UTodoStateArray* AddTodo(const UTodoStateArray* State, const UAction* Action)
{
	const UAddTodoAction* AddTodoAction = Action->CastToAddTodoAction();
	check(AddTodoAction);

	TArray<UTodoState*> NewArray;
	NewArray = State->GetArray(); // Shallow Copy

	UTodoState* NewTodoState = NewObject<UTodoState>();
	NewTodoState->Id = AddTodoAction->Id;
	NewTodoState->Text = UStateText::Create(AddTodoAction->Text);
	NewTodoState->bCompleted = false;
	NewArray.Add(NewTodoState);

	return UTodoStateArray::Create(MoveTemp(NewArray));
}

const UTodoStateArray* ToggleTodo(const UTodoStateArray* State, const UAction* Action)
{
	const UToggleTodoAction* ToggleTodoAction = Action->CastToToggleTodoAction();
	check(ToggleTodoAction);

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

	switch (Action->GetType())
	{
	case EActionType::ADD_TODO: return AddTodo(State, Action);
	case EActionType::TOGGLE_TODO: return ToggleTodo(State, Action);
	}

	return State;
}
