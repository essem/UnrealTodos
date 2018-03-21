// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Reducer.h"

class UTodoStateArray;

class FTodosReducer : public FLeafReducer<UTodoStateArray>
{
public:
	FTodosReducer();
	virtual const UTodoStateArray* GetInitialState() const override;
};
