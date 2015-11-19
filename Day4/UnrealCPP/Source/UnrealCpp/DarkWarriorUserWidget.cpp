// Fill out your copyright notice in the Description page of Project Settings.

#include "UnrealCpp.h"
#include "DarkWarriorUserWidget.h"


void UDarkWarriorUserWidget::NativeConstruct()
{
	DarkWarrior = Cast<ADarkWarriorCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (DarkWarrior == nullptr)
	{
		UE_LOG(LogTemp, Fatal, TEXT("No DarkWarrior"));
	}
}

