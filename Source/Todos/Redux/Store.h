// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Store.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnStateChanged, const UAppState*, State, const UAppState*, PrevState);

UCLASS()
class TODOS_API UStore : public UObject
{
	GENERATED_BODY()

public:
	void Init();
	const UAppState& GetAppState() const;

	UFUNCTION(BlueprintCallable, Category = "Redux")
	void Dispatch(const UAction* Action);

	UPROPERTY(BlueprintAssignable, Category = "Redux")
	FOnStateChanged OnStateChanged;

private:
	void DumpAction(const UAction& Action) const;
	void DumpState(const UAppState& State) const;

	UPROPERTY()
	UAppState* State;

	UPROPERTY()
	UAppState* PrevState;
};
