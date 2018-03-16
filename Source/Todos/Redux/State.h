// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "State.generated.h"

UCLASS(BlueprintType, Abstract)
class UReduxState : public UObject
{
	GENERATED_BODY()

public:
	virtual TSharedPtr<FJsonValue> toJSON() const;
};

UCLASS(BlueprintType)
class UStateString : public UReduxState
{
	GENERATED_BODY()

public:
	void Init(const TCHAR* InitialString);

	UFUNCTION(BlueprintPure, Category = "Redux")
	const FString& GetString() const;

	virtual TSharedPtr<FJsonValue> toJSON() const;

private:
	FString String;
};

UCLASS(BlueprintType)
class UTodoState : public UReduxState
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
class UTodoStateArray : public UReduxState
{
	GENERATED_BODY()

public:
	void Init(TArray<UTodoState*>&& InitialArray);

	UFUNCTION(BlueprintPure, Category = "Redux")
	const TArray<UTodoState*>& GetArray() const;

	virtual TSharedPtr<FJsonValue> toJSON() const;

private:
	UPROPERTY()
	TArray<UTodoState*> Array;
};

UCLASS(BlueprintType)
class UAppState : public UReduxState
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	const UTodoStateArray* Todos;

	UPROPERTY(BlueprintReadOnly)
	const UStateString* VisibilityFilter;
};
