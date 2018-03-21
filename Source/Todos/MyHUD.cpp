// Fill out your copyright notice in the Description page of Project Settings.

#include "MyHUD.h"
#include "Redux/Store.h"

void AMyHUD::BeginPlay()
{
	Store = NewObject<UStore>();
	Store->Init();

	Super::BeginPlay(); // Will create HUDWidget
}

UStore* AMyHUD::GetStore()
{
	return Store;
}
