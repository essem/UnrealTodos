// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MyHUD.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnStateChanged, const UAppState*, State, const UAppState*, PrevState);

UCLASS()
class TODOS_API AMyHUD : public AHUD
{
	GENERATED_BODY()

	virtual void BeginPlay() override;
	
public:
	UFUNCTION(BlueprintCallable, Category = "Redux")
	void Dispatch(const UAction* Action);

	UPROPERTY(BlueprintAssignable, Category = "Redux")
	FOnStateChanged OnStateChanged;

private:
	UPROPERTY()
	UAppState* State;

	UPROPERTY()
	UAppState* PrevState;
};
