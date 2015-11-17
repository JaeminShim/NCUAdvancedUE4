// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "MyUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class LOCEXAMPLE_API UMyUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LOCLabel")
		FText LevelText;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LOCLabel")
		FText SkillText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LOCLabel")
		FText InvenText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LOCLabel")
		FText RubyShopText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LOCLabel")
		FText RankingText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LOCLabel")
		FText MissionText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LOCLabel")
		FText EnterText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LOCLabel")
		FText GambleText;
};
