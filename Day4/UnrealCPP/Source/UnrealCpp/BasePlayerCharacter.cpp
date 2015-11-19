// Fill out your copyright notice in the Description page of Project Settings.

#include "UnrealCpp.h"
#include "PlayerSaveGame.h"
#include "BasePlayerCharacter.h"



ABasePlayerCharacter::ABasePlayerCharacter()
{
	if (nullptr == ExpDataSource)
	{
		static ConstructorHelpers::FObjectFinder<UDataTable> DT_PlayerExp(TEXT("DataTable'/Game/GameData/DT_PlayerExp.DT_PlayerExp'"));
		ExpDataSource = DT_PlayerExp.Object;
	}

	if (nullptr != ExpDataSource)
	{
		//MaxLevel = ExpDataSource->GetTableData().Num();	// for EDITOR
		MaxLevel = ExpDataSource->RowMap.Num();
	}

	SaveSlot = TEXT("PlayerSaveGame1");
}

void ABasePlayerCharacter::InitCharacterData()
{
	Super::InitCharacterData();

	UPlayerSaveGame* SaveGameInstance = Cast<UPlayerSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveSlot, 0));
	if (nullptr == SaveGameInstance)
	{
		CharacterLevel = 1;
		CurrentExp = 0;
	}
	else
	{
		CharacterLevel = SaveGameInstance->CharacterLevel;
		CurrentExp = SaveGameInstance->CurrentExp;
	}

	//if (nullptr != ExpDataSource && ExpDataSource->GetTableData().IsValidIndex(CharacterLevel))
	FName IndexName = FName(*FString::FromInt(CharacterLevel));
	if (nullptr != ExpDataSource && ExpDataSource->RowMap.Contains(IndexName))
	{
		auto CurrentRow = ExpDataSource->FindRow<FExpData>(IndexName, FString(TEXT("ExpData")));
		if (nullptr != CurrentRow)
			NextExp = CurrentRow->Exp;
	}
}

void ABasePlayerCharacter::SetLevel(int32 NewLevel)
{
	if (NewLevel > MaxLevel)
		return;

	CharacterLevel = NewLevel;
	//if (nullptr != ExpDataSource && ExpDataSource->GetTableData().IsValidIndex(CharacterLevel))
	FName IndexName = FName(*FString::FromInt(CharacterLevel));
	if (nullptr != ExpDataSource && ExpDataSource->RowMap.Contains(IndexName))
	{
		auto CurrentRow = ExpDataSource->FindRow<FExpData>(IndexName, FString(TEXT("ExpData")));
		if (nullptr != CurrentRow)
			NextExp = CurrentRow->Exp;
	}
	CurrentExp = 0;
	CurrentHP = MaxHP;

	OnLevelUp.ExecuteIfBound();
}

void ABasePlayerCharacter::ReceiveExp(int32 NewExp)
{
	CurrentExp = FMath::Clamp<int32>(CurrentExp + NewExp, 0, NextExp);
	if (CurrentExp == NextExp)
	{
		if (CharacterLevel < MaxLevel)
			SetLevel(++CharacterLevel);
	}

	UPlayerSaveGame* SaveGameInstance = Cast<UPlayerSaveGame>(UGameplayStatics::CreateSaveGameObject(UPlayerSaveGame::StaticClass()));
	SaveGameInstance->CharacterLevel = CharacterLevel;
	SaveGameInstance->CurrentExp = CurrentExp;
	if (!UGameplayStatics::SaveGameToSlot(SaveGameInstance, SaveSlot, 0))
	{
		UE_LOG(LogTemp, Warning, TEXT("Save Failed!"));
	}
}
