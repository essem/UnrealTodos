// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class UStateString;
class UAction;

const UStateString* VisibilityFilterReducer(const UStateString* State, const UAction* Action);
