// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Reducer.h"
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Store.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnStateChanged, const UAppState*, State, const UAppState*, PrevState);

UCLASS()
class TODOS_API UStore : public UObject
{
	GENERATED_BODY()

public:
	UStore();
	void Init(TSharedPtr<FReducer<UAppState>> InRootReducer);
	const UAppState& GetAppState() const;

	UFUNCTION(BlueprintCallable, Category = "Redux")
	void Dispatch(const UAction* Action);

	UFUNCTION(BlueprintPure, Category = "Redux")
	bool CanUndo() const;

	UFUNCTION(BlueprintCallable, Category = "Redux")
	void Undo();

	UFUNCTION(BlueprintPure, Category = "Redux")
	bool CanRedo() const;

	UFUNCTION(BlueprintCallable, Category = "Redux")
	void Redo();

	UPROPERTY(BlueprintAssignable, Category = "Redux")
	FOnStateChanged OnStateChanged;

private:
	void DumpAction(const UAction& Action) const;
	void DumpState(const UAppState& State) const;

	UPROPERTY()
	TArray<const UAppState*> States;

	TSharedPtr<FReducer<UAppState>> RootReducer;

	int32 CurrentStateIndex;
};
