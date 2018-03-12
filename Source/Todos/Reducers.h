// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class UTodoState;
class UAction;

TArray<UTodoState*> TodosReducer(const TArray<UTodoState*>* State, const UAction* Action);
FString VisibilityFilterReducer(const FString* State, const UAction* Action);
