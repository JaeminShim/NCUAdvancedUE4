// Fill out your copyright notice in the Description page of Project Settings.

#include "UnrealCpp.h"
#include "DarkWarriorCharacter.h"
#include "DarkWarriorPlayerController.h"
#include "DarkWarriorGameMode.h"

ADarkWarriorGameMode::ADarkWarriorGameMode()
{
	DefaultPawnClass = ADarkWarriorCharacter::StaticClass();
	PlayerControllerClass = ADarkWarriorPlayerController::StaticClass();
}


