// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BaseCharacter.h"
#include "BasePlayerCharacter.generated.h"

USTRUCT(BlueprintType)
struct FExpData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY();

public:
	FExpData() : Exp(0) {}

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category="Data")
	int32 Exp;
};

DECLARE_DELEGATE(FCharacterLevelUpDelegate);

/**
 * 
 */
UCLASS()
class UNREALCPP_API ABasePlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	ABasePlayerCharacter();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="GameData")
	class UDataTable* ExpDataSource;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "GameData")
	int32 CurrentExp;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "GameData")
	int32 NextExp;

public:
	UFUNCTION(BlueprintCallable, Category = "GamePlay")
	virtual void InitCharacterData() override;

	UFUNCTION(BlueprintCallable, Category="GamePlay")
	void ReceiveExp(int32 NewExp);

	UFUNCTION(BlueprintCallable, Category = "GamePlay")
	float GetExpPercent() const { return (float)CurrentExp / (float)NextExp; }

protected:
	UFUNCTION(BlueprintCallable, Category = "GamePlay")
	virtual void SetLevel(int32 NewLevel);

	FCharacterLevelUpDelegate OnLevelUp;

	FString SaveSlot;

	int32 MaxLevel;
};
