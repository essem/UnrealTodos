// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Actions.generated.h"

UENUM()
enum class EActionType
{
	INVALID,
	ADD_TODO,
	TOGGLE_TODO,
	SET_VISIBILITY_FILTER,
};

UCLASS()
class UAction : public UObject
{
	GENERATED_BODY()

public:
	virtual EActionType GetType() const { check(0 && "You must override this"); return EActionType::INVALID; };
	virtual UStruct* GetStaticStruct() const { check(0 && "You must override this"); return nullptr; };
	virtual const class UAddTodoAction* CastToAddTodoAction() const { return nullptr; }
	virtual const class USetVisibilityFilterAction* CastToSetVisibilityFilterAction() const { return nullptr; }
	virtual const class UToggleTodoAction* CastToToggleTodoAction() const { return nullptr; }
};

UCLASS(BlueprintType)
class UAddTodoAction : public UAction
{
	GENERATED_BODY()

public:
	virtual EActionType GetType() const override { return EActionType::ADD_TODO; }
	virtual const UAddTodoAction* CastToAddTodoAction() const override { return this; }
	virtual UStruct* GetStaticStruct() const override { return UAddTodoAction::StaticClass(); };

	UPROPERTY(BlueprintReadWrite)
	int32 Id;

	UPROPERTY(BlueprintReadWrite)
	FText Text;
};

UCLASS(BlueprintType)
class UToggleTodoAction : public UAction
{
	GENERATED_BODY()

public:
	virtual EActionType GetType() const override { return EActionType::TOGGLE_TODO; }
	virtual const UToggleTodoAction* CastToToggleTodoAction() const override { return this; }
	virtual UStruct* GetStaticStruct() const override { return UToggleTodoAction::StaticClass(); };

	UPROPERTY(BlueprintReadWrite)
	int32 Id;
};

UCLASS(BlueprintType)
class USetVisibilityFilterAction : public UAction
{
	GENERATED_BODY()

public:
	virtual EActionType GetType() const override { return EActionType::SET_VISIBILITY_FILTER; }
	virtual const USetVisibilityFilterAction* CastToSetVisibilityFilterAction() const override { return this; }
	virtual UStruct* GetStaticStruct() const override { return USetVisibilityFilterAction::StaticClass(); };

	UPROPERTY(BlueprintReadWrite)
	FString Filter;
};
