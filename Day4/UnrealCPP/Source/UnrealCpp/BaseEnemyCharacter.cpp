// Fill out your copyright notice in the Description page of Project Settings.

#include "UnrealCpp.h"
#include "BaseEnemyCharacter.h"


ABaseEnemyCharacter::ABaseEnemyCharacter()
{
	if (CharacterClass.IsEmpty())
		CharacterClass = TEXT("Bear");

	TestComponent1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Test1"));
	TestComponent2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Test2"));
}

