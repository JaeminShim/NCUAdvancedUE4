// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BaseCharacter.h"
#include "BaseEnemyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class UNREALCPP_API ABaseEnemyCharacter : public ABaseCharacter
{
	GENERATED_BODY()
	
public:
	ABaseEnemyCharacter();

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category="GameData")
	int32 Exp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "GameData")
	class UStaticMeshComponent* TestComponent1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameData")
	class UStaticMeshComponent* TestComponent2;
};
