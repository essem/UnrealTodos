// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class UTodoStateArray;
class UAction;

const UTodoStateArray* TodosReducer(const UTodoStateArray* State, const UAction* Action);
