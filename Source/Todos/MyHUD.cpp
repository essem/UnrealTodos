// Fill out your copyright notice in the Description page of Project Settings.

#include "MyHUD.h"
#include "Actions.h"

USTRUCT(BlueprintType)
struct FTodoState
{
	UPROPERTY(BlueprintReadOnly)
	int32 Id;

	UPROPERTY(BlueprintReadOnly)
	FText Text;

	UPROPERTY(BlueprintReadOnly)
	bool bCompleted;
};

USTRUCT(BlueprintType)
struct FAppState
{
	UPROPERTY(BlueprintReadOnly)
	TSharedPtr<const TArray<FTodoState>> Todos;

	UPROPERTY(BlueprintReadOnly)
	TSharedPtr<const FString> VisibilityFilter;
};

//const todos = (state = [], action) = > {
//	switch (action.type) {
//	case 'TOGGLE_TODO':
//		return state.map(todo = >
//			(todo.id == = action.id)
//			? {...todo, completed: !todo.completed}
//		: todo
//			)
//	default:
//		return state
//	}
//}
//
//export default todos

const TArray<FTodoState>* TodosReducer(const TArray<FTodoState>* State, const UAction* Action)
{
	if (!State)
	{
		return new TArray<FTodoState>;
	}

	switch (Action->GetType()) {
	case EActionType::ADD_TODO:
		{
			const UAddTodoAction* AddTodoAction = Action->CastToAddTodoAction();
			TArray<FTodoState>* NewState = new TArray<FTodoState>;
			*NewState = *State;
			FTodoState TodoState;
			TodoState.Id = AddTodoAction->Id;
			TodoState.Text = AddTodoAction->Text;
			TodoState.bCompleted = false;
			NewState->Add(TodoState);
			return NewState;
		}
	default:
		return State;
	}
}

const FString* VisibilityFilterReducer(const FString* State, const UAction* Action)
{
	if (!State)
	{
		return new FString("SHOW_ALL");
	}

	switch (Action->GetType()) {
	case EActionType::SET_VISIBILITY_FILTER:
		return new FString(Action->CastToSetVisibilityFilterAction()->Filter);
	default:
		return State;
	}
}

void AMyHUD::BeginPlay()
{
	Super::BeginPlay();

	State = MakeShareable(new FAppState());
	State->Todos = MakeShareable(TodosReducer(nullptr, nullptr));
	State->VisibilityFilter = MakeShareable(VisibilityFilterReducer(nullptr, nullptr));
}

UAction* AMyHUD::CreateAction(UObject* WorldContextObject, TSubclassOf<UAction> ActionClass)
{
	UWorld* World = GEngine->GetWorldFromContextObjectChecked(WorldContextObject);
	return NewObject<UAction>(World, ActionClass);
}

void AMyHUD::Dispatch(const UAction* Action)
{
	if (!Action)
	{
		return;
	}

	State->Todos = MakeShareable(TodosReducer(State->Todos.Get(), Action));
	State->VisibilityFilter = MakeShareable(VisibilityFilterReducer(State->VisibilityFilter.Get(), Action));

	const UAddTodoAction* AddTodoAction = Action->CastToAddTodoAction();
	if (AddTodoAction)
	{
		UE_LOG(LogTemp, Warning, TEXT("AddTodoAction: Id(%d), Text(%s)"), AddTodoAction->Id, *AddTodoAction->Text.ToString());
	}
}
