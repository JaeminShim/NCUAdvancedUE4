// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DarkWarriorCharacter.h"
#include "Animation/AnimInstance.h"
#include "DarkWarriorAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class UNREALCPP_API UDarkWarriorAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	float CurrentVelocitySquared;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	TEnumAsByte<EDarkWarriorStates> CurrentAnimState;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character")
	class ADarkWarriorCharacter* DarkWarrior;

	UFUNCTION(BlueprintCallable, Category = "AnimEvent")
	void OnAttackHit();

};
