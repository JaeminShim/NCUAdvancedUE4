// Fill out your copyright notice in the Description page of Project Settings.

#include "UnrealCpp.h"
#include "UMG.h"
#include "DarkWarriorUserWidget.h"
#include "DarkWarriorPlayerController.h"

ADarkWarriorPlayerController::ADarkWarriorPlayerController()
{
	bShowMouseCursor = true;
	static ConstructorHelpers::FClassFinder<UUserWidget> UMGPanel2(TEXT("/Game/HUD/UI/UMGPanel2"));
	WidgetClass = UMGPanel2.Class;

}

void ADarkWarriorPlayerController::BeginPlay()
{
	CreateWidget<UUserWidget>(this, WidgetClass)->AddToViewport();
}
