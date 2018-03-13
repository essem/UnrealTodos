// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ReduxBlueprintFunctionLibrary.generated.h"

class UAction;
class UAppState;

UCLASS()
class TODOS_API UReduxBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintPure, meta = (HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject", DisplayName = "Create Action", CompactNodeTitle = "Create"), Category = "Redux")
	static UAction* CreateAction(UObject* WorldContextObject, TSubclassOf<UAction> ActionClass);

	UFUNCTION(BlueprintCallable, meta = (HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject", DisplayName = "Dispatch Action", CompactNodeTitle = "Dispatch"), Category = "Redux")
	static void Dispatch(UObject* WorldContextObject, const UAction* Action);

	UFUNCTION(BlueprintPure, meta = (HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject", DisplayName = "Get Application State", CompactNodeTitle = "AppState"), Category = "Redux")
	static UAppState* GetAppState(UObject* WorldContextObject);
};
