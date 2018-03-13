// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "State.generated.h"

UCLASS(BlueprintType)
class UTodoState : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	int32 Id;

	UPROPERTY(BlueprintReadOnly)
	FText Text;

	UPROPERTY(BlueprintReadOnly)
	bool bCompleted;
};

UCLASS(BlueprintType)
class UAppState : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	TArray<UTodoState*> Todos;

	UPROPERTY(BlueprintReadOnly)
	FString VisibilityFilter;
};
