// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/SaveGame.h"
#include "PlayerSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class UNREALCPP_API UPlayerSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UPlayerSaveGame() : CharacterLevel(1), CurrentExp(0) { }

	UPROPERTY()
	int32 CharacterLevel;

	UPROPERTY()
	int32 CurrentExp;
};
