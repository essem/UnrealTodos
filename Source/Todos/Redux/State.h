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
	virtual TSharedPtr<FJsonValue> ToJson() const;
};

UCLASS(BlueprintType)
class UStateString : public UReduxState
{
	GENERATED_BODY()

public:
	static UStateString* Create(const TCHAR* InitialString);
	static UStateString* Create(const FString& InitialString);
	static UStateString* Create(FString&& InitialString);

	UFUNCTION(BlueprintPure, Category = "Redux")
	const FString& GetString() const;

	virtual TSharedPtr<FJsonValue> ToJson() const;

private:
	void Init(FString&& InitialString);

	FString String;
};

UCLASS(BlueprintType)
class UStateText : public UReduxState
{
	GENERATED_BODY()

public:
	static UStateText* Create(const FText& InitialText);
	static UStateText* Create(FText&& InitialText);

	UFUNCTION(BlueprintPure, Category = "Redux")
	const FText& GetText() const;

	virtual TSharedPtr<FJsonValue> ToJson() const;

private:
	void Init(FText&& InitialText);

	FText Text;
};

UCLASS(BlueprintType)
class UTodoState : public UReduxState
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	int32 Id;

	UPROPERTY(BlueprintReadOnly)
	UStateText* Text;

	UPROPERTY(BlueprintReadOnly)
	bool bCompleted;
};

UCLASS(BlueprintType)
class UTodoStateArray : public UReduxState
{
	GENERATED_BODY()

public:
	static UTodoStateArray* Create(TArray<UTodoState*>&& InitialArray);

	UFUNCTION(BlueprintPure, Category = "Redux")
	const TArray<UTodoState*>& GetArray() const;

	virtual TSharedPtr<FJsonValue> ToJson() const;

private:
	void Init(TArray<UTodoState*>&& InitialArray);

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
