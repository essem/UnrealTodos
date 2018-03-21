// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Reducer.h"

class UStateString;

class FVisibilityFilterReducer : public FLeafReducer<UStateString>
{
public:
	FVisibilityFilterReducer();
	virtual const UStateString* GetInitialState() const override;
};
