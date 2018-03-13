// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MyHUD.generated.h"

class UStore;

UCLASS()
class TODOS_API AMyHUD : public AHUD
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Redux")
	UStore* GetStore();

private:
	virtual void BeginPlay() override;

	UPROPERTY()
	UStore* Store;
};
