// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Actions.h"
#include "MyHUD.generated.h"

UCLASS()
class TODOS_API AMyHUD : public AHUD
{
	GENERATED_BODY()

	virtual void BeginPlay() override;
	
public:
	UFUNCTION(BlueprintPure, meta = (HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject", DisplayName = "Create Action", CompactNodeTitle = "Create"), Category = "Redux")
	static UAction* CreateAction(UObject* WorldContextObject, TSubclassOf<UAction> ActionClass);

	UFUNCTION(BlueprintCallable, Category = "Redux")
	void Dispatch(const UAction* Action);

private:
	TSharedPtr<struct FAppState> State;
};
