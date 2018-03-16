// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "State.generated.h"

UCLASS(BlueprintType)
class UStateString : public UObject
{
	GENERATED_BODY()

public:
	void Init(const TCHAR* InitialString);

	UFUNCTION(BlueprintPure, Category = "Redux")
	const FString& GetString() const;

private:
	FString String;
};

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
class UTodoStateArray : public UObject
{
	GENERATED_BODY()

public:
	void Init(TArray<UTodoState*>&& InitialArray);

	UFUNCTION(BlueprintPure, Category = "Redux")
	const TArray<UTodoState*>& GetArray() const;

private:
	UPROPERTY()
	TArray<UTodoState*> Array;
};

UCLASS(BlueprintType)
class UAppState : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	const UTodoStateArray* Todos;

	UPROPERTY(BlueprintReadOnly)
	const UStateString* VisibilityFilter;
};
