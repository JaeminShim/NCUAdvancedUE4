// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "DarkWarriorCharacter.h"
#include "DarkWarriorUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class UNREALCPP_API UDarkWarriorUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;
	
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character")
	ADarkWarriorCharacter* DarkWarrior;
};
