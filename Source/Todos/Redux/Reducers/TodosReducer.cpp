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

#if WITH_EDITOR

#define ASSERT_EQUAL(x,y) if ((x)!=(y)) { return false; }
#define ASSERT_EQUAL_TEXT(x,y) if (!(x).EqualTo(y)) { return false; }

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FTodosReducerInitialStateTest, "Redux.TodosReducer.InitialState", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool FTodosReducerInitialStateTest::RunTest(const FString& Parameters)
{
	const UTodoStateArray* State = TodosReducer(nullptr, nullptr);
	ASSERT_EQUAL(State->GetArray().Num(), 0);

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FTodosReducerAddTodoTest, "Redux.TodosReducer.AddTodo", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool FTodosReducerAddTodoTest::RunTest(const FString& Parameters)
{
	const UTodoStateArray* State = UTodoStateArray::Create(TArray<UTodoState*>());
	UAddTodoAction* Action = NewObject<UAddTodoAction>();
	Action->Text = FText::FromString("Run the tests");
	Action->Id = 0;

	const UTodoStateArray* NewState = TodosReducer(State, Action);
	ASSERT_EQUAL(NewState->GetArray().Num(), 1);
	ASSERT_EQUAL_TEXT(NewState->GetArray()[0]->Text->GetText(), FText::FromString("Run the tests"));
	ASSERT_EQUAL(NewState->GetArray()[0]->bCompleted, false);
	ASSERT_EQUAL(NewState->GetArray()[0]->Id, 0);

	State = NewState;
	Action = NewObject<UAddTodoAction>();
	Action->Text = FText::FromString("Use Redux");
	Action->Id = 1;

	NewState = TodosReducer(State, Action);
	ASSERT_EQUAL(NewState->GetArray().Num(), 2);
	ASSERT_EQUAL_TEXT(NewState->GetArray()[0]->Text->GetText(), FText::FromString("Run the tests"));
	ASSERT_EQUAL(NewState->GetArray()[0]->bCompleted, false);
	ASSERT_EQUAL(NewState->GetArray()[0]->Id, 0);
	ASSERT_EQUAL_TEXT(NewState->GetArray()[1]->Text->GetText(), FText::FromString("Use Redux"));
	ASSERT_EQUAL(NewState->GetArray()[1]->bCompleted, false);
	ASSERT_EQUAL(NewState->GetArray()[1]->Id, 1);

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FTodosReducerToggleTodoTest, "Redux.TodosReducer.ToggleTodo", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool FTodosReducerToggleTodoTest::RunTest(const FString& Parameters)
{
	TArray<UTodoState*> NewArray;

	UTodoState* TodoState = NewObject<UTodoState>();
	TodoState->Id = 0;
	TodoState->Text = UStateText::Create(FText::FromString("Run the tests"));
	TodoState->bCompleted = false;
	NewArray.Add(TodoState);

	TodoState = NewObject<UTodoState>();
	TodoState->Id = 1;
	TodoState->Text = UStateText::Create(FText::FromString("Use Redux"));
	TodoState->bCompleted = false;
	NewArray.Add(TodoState);

	const UTodoStateArray* State = UTodoStateArray::Create(MoveTemp(NewArray));

	UToggleTodoAction* Action = NewObject<UToggleTodoAction>();
	Action->Id = 1;

	const UTodoStateArray* NewState = TodosReducer(State, Action);
	ASSERT_EQUAL(NewState->GetArray().Num(), 2);
	ASSERT_EQUAL_TEXT(NewState->GetArray()[0]->Text->GetText(), FText::FromString("Run the tests"));
	ASSERT_EQUAL(NewState->GetArray()[0]->bCompleted, false);
	ASSERT_EQUAL(NewState->GetArray()[0]->Id, 0);
	ASSERT_EQUAL_TEXT(NewState->GetArray()[1]->Text->GetText(), FText::FromString("Use Redux"));
	ASSERT_EQUAL(NewState->GetArray()[1]->bCompleted, true);
	ASSERT_EQUAL(NewState->GetArray()[1]->Id, 1);

	return true;
}

#endif
