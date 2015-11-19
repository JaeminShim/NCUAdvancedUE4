// Fill out your copyright notice in the Description page of Project Settings.

#include "UnrealCpp.h"
#include "Kismet/KismetMathLibrary.h"
#include "BaseCharacter.h"


// Sets default values
ABaseCharacter::ABaseCharacter()
{
	if (nullptr == CharacterDataSource)
	{
		static ConstructorHelpers::FObjectFinder<UDataTable> DT_Character(TEXT("DataTable'/Game/GameData/DT_Character.DT_Character'"));
		CharacterDataSource = DT_Character.Object;
	}

	if (nullptr == DamageCurveSource)
	{
		static ConstructorHelpers::FObjectFinder<UCurveTable> DT_Damage(TEXT("CurveTable'/Game/GameData/DT_Damage.DT_Damage'"));
		DamageCurveSource = DT_Damage.Object;
	}
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	InitCharacterData();
}

//// Called every frame
//void ABaseCharacter::Tick( float DeltaTime )
//{
//	Super::Tick( DeltaTime );
//
//}

//// Called to bind functionality to input
//void ABaseCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
//{
//	Super::SetupPlayerInputComponent(InputComponent);
//
//}

float ABaseCharacter::GetFinalAttackDamage()
{
	float AttackDamage = DamageCurve.Eval((float)CharacterLevel);
	//return FMath::RandRange(AttackDamage, AttackDamage * 1.2f);
	return UKismetMathLibrary::RandomFloatInRange(AttackDamage, AttackDamage * 1.2f);
}

void ABaseCharacter::InitCharacterData()
{
	if (nullptr != CharacterDataSource)
	{
		uint32 RecordCount = CharacterDataSource->RowMap.Num();
		for (uint32 i = 0; i < RecordCount; ++i)
		{
			FName IndexName = FName(*FString::FromInt(i));
			FCharacterData* CurrentRow = CharacterDataSource->FindRow<FCharacterData>(
				IndexName, FString(TEXT("CharacterDataSource"))
				);
			if (CurrentRow && CurrentRow->Class.Equals(CharacterClass))
			{
				CharacterData = *CurrentRow;
			}
		}
	}

	if (nullptr != DamageCurveSource)
	{
		FRichCurve* TargetCurve = DamageCurveSource->FindCurve(
			FName(*CharacterClass), FString(TEXT("DamageCurveData"))
			);
		if (nullptr != TargetCurve)
		{
			DamageCurve = *TargetCurve;
		}
	}

	AttackRange = CharacterData.AttackRange;
	MaxHP = CharacterData.BaseHP;
	GetCharacterMovement()->MaxWalkSpeed = CharacterData.MoveSpeed;
	CurrentHP = MaxHP;
}
