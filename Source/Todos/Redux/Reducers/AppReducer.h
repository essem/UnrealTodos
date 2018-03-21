// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class UAppState;
class UAction;

const UAppState* AppReducer(const UAppState* State, const UAction* Action);
