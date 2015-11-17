// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UMG.h"
#include "GameFramework/PlayerController.h"
#include "DarkWarriorPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class UNREALCPP_API ADarkWarriorPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ADarkWarriorPlayerController();

	virtual void BeginPlay() override;
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "HUD")
	TSubclassOf<class UUserWidget> WidgetClass;
	
};
