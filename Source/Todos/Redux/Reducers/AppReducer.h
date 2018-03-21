// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Reducer.h"
#include "TodosReducer.h"
#include "VisibilityFilterReducer.h"

class FAppReducer : public FReducer<UAppState>
{
public:
	virtual const UAppState* GetInitialState() const override;
	virtual const UAppState* Reduce(const UAppState* State, const UAction* Action) const override;

private:
	FTodosReducer TodosReducer;
	FVisibilityFilterReducer VisibilityFilterReducer;
};
