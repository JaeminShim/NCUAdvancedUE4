// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BasePlayerCharacter.h"
#include "DarkWarriorCharacter.generated.h"


UENUM(BlueprintType)
enum EDarkWarriorStates
{
	PEACE UMETA(DisplayName = "Peace"),
	BATTLE UMETA(DisplayName = "Battle"),
	DEAD UMETA(DisplayName = "Dead")
};

UCLASS()
class UNREALCPP_API ADarkWarriorCharacter : public ABasePlayerCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ADarkWarriorCharacter();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
	class USkeletalMeshComponent* Weapon;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	class UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Effect")
	class UParticleSystemComponent* DamageEffect;


public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	TEnumAsByte<EDarkWarriorStates> CurrentState;
	
	UFUNCTION(BlueprintCallable, Category = "Input")
	void DoAttack();

	UFUNCTION(BlueprintCallable, Category = "AnimEvent")
	void AttackEnd();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "AnimEvent")
	void AttackHit();
	virtual void AttackHit_Implementation();

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	//float AttackRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	float AttackRadius;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	//float AttackDamage;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	//float CurrentHP;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	//float MaxHP;

	UFUNCTION()
	void PointDamageEvent(float Damage, class AController* InstigatedBy, FVector HitLocation, class UPrimitiveComponent* FHitComponent, FName BoneName, FVector ShotFromDirection, const class UDamageType* DamageType, AActor* DamageCauser);

	UFUNCTION()
	void ReloadLevel();

private:
	float CurrentLeftRightVal;
	float CurrentUpDownVal;
	FTimerHandle ReloadTimerHandle;

	void UpDownInput(float NewInputVal);
	void LeftRightInput(float NewInputval);

	uint32 bInAction : 1;
};
