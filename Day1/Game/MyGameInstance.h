// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#if PLATFORM_ANDROID
#include "Android/AndroidJNI.h"
#include "AndroidJava.h"
#endif
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class DAY1_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()

	virtual void Init() override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Player Info")
	FString PhoneNumber;
};
