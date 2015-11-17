// Fill out your copyright notice in the Description page of Project Settings.

#include "UnrealCpp.h"
#include "DarkWarriorAnimInstance.h"


void UDarkWarriorAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	APawn* PawnOwner = TryGetPawnOwner();
	if (PawnOwner != nullptr && PawnOwner->IsValidLowLevel())
	{
		DarkWarrior = Cast<ADarkWarriorCharacter>(PawnOwner);
		if (DarkWarrior != nullptr)
		{
			CurrentAnimState = DarkWarrior->CurrentState;
			CurrentVelocitySquared = DarkWarrior->GetVelocity().SizeSquared2D();
		}
	}
}

void UDarkWarriorAnimInstance::OnAttackHit()
{
	DarkWarrior->AttackHit_Implementation();
}

