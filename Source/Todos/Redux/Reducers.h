// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class UAppState;
class UStateString;
class UTodoStateArray;
class UAction;

const UAppState* AppReducer(const UAppState* State, const UAction* Action);
const UTodoStateArray* TodosReducer(const UTodoStateArray* State, const UAction* Action);
const UStateString* VisibilityFilterReducer(const UStateString* State, const UAction* Action);
