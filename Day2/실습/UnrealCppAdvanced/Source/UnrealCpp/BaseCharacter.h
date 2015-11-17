// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

USTRUCT(BlueprintType)
struct FCharacterData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY();

public:
	FCharacterData()
		: Class(TEXT("None")), BaseHP(100), MoveSpeed(600.0f), AttackRange(150.0f), SkillAttackRange(400.0f)
	{ }

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FString Class;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 BaseHP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float MoveSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float AttackRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float SkillAttackRange;
};


UCLASS()
class UNREALCPP_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	//// Called every frame
	//virtual void Tick( float DeltaSeconds ) override;

	//// Called to bind functionality to input
	//virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;


	// Table references
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "GameData")
	class UDataTable* CharacterDataSource;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "GameData")
	class UCurveTable* DamageCurveSource;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "GamePlay")
	FString CharacterClass;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "GamePlay")
	int32 CharacterLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GamePlay")
	float AttackRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GamePlay")
	float CurrentHP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GamePlay")
	float MaxHP;

protected:
	UFUNCTION(BlueprintCallable, Category = "GamePlay")
	float GetFinalAttackDamage();

	UFUNCTION(BlueprintCallable, Category = "GamePlay")
	virtual void InitCharacterData();

	// Cached table data
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameData")
	FCharacterData CharacterData;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameData")
	FRichCurve DamageCurve;
};
