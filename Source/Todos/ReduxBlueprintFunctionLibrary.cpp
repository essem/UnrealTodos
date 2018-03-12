// Fill out your copyright notice in the Description page of Project Settings.

#include "ReduxBlueprintFunctionLibrary.h"
#include "Actions.h"
#include "MyHUD.h"

UAction* UReduxBlueprintFunctionLibrary::CreateAction(UObject* WorldContextObject, TSubclassOf<UAction> ActionClass)
{
	UWorld* World = GEngine->GetWorldFromContextObjectChecked(WorldContextObject);
	return NewObject<UAction>(World, ActionClass);
}

void UReduxBlueprintFunctionLibrary::Dispatch(UObject* WorldContextObject, const UAction* Action)
{
	UWorld* World = GEngine->GetWorldFromContextObjectChecked(WorldContextObject);
	AMyHUD* MyHUD = Cast<AMyHUD>(World->GetFirstPlayerController()->GetHUD());
	MyHUD->Dispatch(Action);
}
