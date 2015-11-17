// Fill out your copyright notice in the Description page of Project Settings.

#include "UnrealCpp.h"
#include "Kismet/KismetMathLibrary.h"
#include "DarkWarriorCharacter.h"


// Sets default values
ADarkWarriorCharacter::ADarkWarriorCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("PlayerProfile"));

	GetMesh()->SetRelativeLocation(FVector(0.0F, 0.0F, -88.0F));
	GetMesh()->SetRelativeRotation(FRotator(0.0F, -90.0F, 0.0F));
	GetMesh()->SetRelativeScale3D(FVector(0.45F, 0.45F, 0.45F));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_DarkWarrior(TEXT("/Game/DarkWarrior/SK_DarkWarrior"));
	GetMesh()->SetSkeletalMesh(SK_DarkWarrior.Object);
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	static ConstructorHelpers::FObjectFinder<UAnimBlueprint> DarkWarrior_AnimBlueprint(TEXT("/Game/DarkWarrior/Blueprint/DarkWarrior_AnimBlueprint2"));
	GetMesh()->AnimBlueprintGeneratedClass = DarkWarrior_AnimBlueprint.Object->GetAnimBlueprintGeneratedClass();

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon"));
	Weapon->AttachParent = GetMesh();
	Weapon->AttachSocketName = TEXT("Hand_Grip");
	Weapon->SetRelativeScale3D(FVector(2.2F, 2.2F, 2.2F));
	Weapon->SetRelativeRotation(FRotator(-45.0F, 0.0F, 30.0F));
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_Sword(TEXT("/Game/InfinityBladeWeapons/Weapons/Blade/Swords/Blade_HeroSword11/SK_Blade_HeroSword11"));
	Weapon->SetSkeletalMesh(SK_Sword.Object);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->AttachParent = GetCapsuleComponent();
	SpringArm->TargetArmLength = 800.0F;
	SpringArm->SetRelativeRotation(FRotator(-60.0F, 0.0F, 0.0F));
	SpringArm->bInheritPitch = false;
	SpringArm->bInheritRoll = false;
	SpringArm->bInheritYaw = false;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->AttachParent = SpringArm;
	Camera->SetRelativeRotation(FRotator::ZeroRotator);

	bUseControllerRotationYaw = false;
	bInAction = false;

	//AttackRange = 150.0F;
	//AttackDamage = 60.0F;
	//MaxHP = 100.0F;
	AttackRadius = 60.0F;

	DamageEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("DamageEffect"));
	DamageEffect->AttachParent = GetCapsuleComponent();
	static ConstructorHelpers::FObjectFinder<UParticleSystem> P_Explosion(TEXT("/Game/Share/Particles/P_Explosion"));
	DamageEffect->SetTemplate(P_Explosion.Object);
	DamageEffect->bAutoActivate = false;

	OnTakePointDamage.AddDynamic(this, &ADarkWarriorCharacter::PointDamageEvent);

	CharacterClass = TEXT("Knight");
}

// Called when the game starts or when spawned
void ADarkWarriorCharacter::BeginPlay()
{
	Super::BeginPlay();
	//UAnimationAsset* RunAsset = Cast<UAnimationAsset>(StaticLoadObject(UAnimationAsset::StaticClass(), NULL, TEXT("/Game/DarkWarrior/Animations/DarkWarrior_Run")));
	//if (RunAsset)
	//{
	//	GetMesh()->PlayAnimation(RunAsset, true);
	//}

	CurrentHP = MaxHP;

	//TEST
	ReceiveExp(100);
}

// Called every frame
void ADarkWarriorCharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	switch (CurrentState)
	{
	case EDarkWarriorStates::PEACE:
		{
			FVector InputVector = FVector(CurrentUpDownVal, CurrentLeftRightVal, 0.0F);
			if (InputVector.SizeSquared() > 0.0F)
			{
				SetActorRotation(UKismetMathLibrary::MakeRotFromX(InputVector));
				AddMovementInput(GetActorForwardVector());
			}
		}
		break;

	default:
		{

		}
	}


}

// Called to bind functionality to input
void ADarkWarriorCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

	InputComponent->BindAxis("LeftRight", this, &ADarkWarriorCharacter::LeftRightInput);
	InputComponent->BindAxis("UpDown", this, &ADarkWarriorCharacter::UpDownInput);

}

void ADarkWarriorCharacter::LeftRightInput(float NewInputVal)
{
	CurrentLeftRightVal = NewInputVal;
}

void ADarkWarriorCharacter::UpDownInput(float NewInputVal)
{
	CurrentUpDownVal = NewInputVal;
}

void ADarkWarriorCharacter::DoAttack()
{
	if (bInAction)
		return;

	UAnimMontage* AnimMontage = Cast<UAnimMontage>(StaticLoadObject(UAnimMontage::StaticClass(), NULL, TEXT("/Game/DarkWarrior/Animations/SK_DarkWarrior_Skeleton_Montage")));
	if (AnimMontage)
	{
		CurrentState = EDarkWarriorStates::BATTLE;
		PlayAnimMontage(AnimMontage, 1.0F, TEXT("Attack"));
		bInAction = true;
	}
}

void ADarkWarriorCharacter::AttackEnd()
{
	CurrentState = EDarkWarriorStates::PEACE;
	bInAction = false;
}

void ADarkWarriorCharacter::AttackHit_Implementation()
{
	FHitResult HitResult(ForceInit);
	FVector StartPos = GetActorLocation();
	FVector EndPos = StartPos + GetActorForwardVector() * AttackRange;
	if (GetWorld()->SweepSingleByChannel(HitResult, StartPos, EndPos, FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel3, FCollisionShape::MakeSphere(AttackRadius)))
	{
		//UGameplayStatics::ApplyPointDamage(HitResult.GetActor(), FMath::FRandRange(AttackDamage, AttackDamage * 0.2F), GetActorForwardVector(), HitResult, GetController(), this, nullptr);
		UGameplayStatics::ApplyPointDamage(HitResult.GetActor(), GetFinalAttackDamage(), GetActorForwardVector(), HitResult, GetController(), this, nullptr);

		//TEST
		ReceiveExp(CharacterLevel * 20);
	}
}

void ADarkWarriorCharacter::PointDamageEvent(float Damage, class AController* InstigatedBy, FVector HitLocation, class UPrimitiveComponent* FHitComponent, FName BoneName, FVector ShotFromDirection, const class UDamageType* DamageType, AActor* DamageCauser)
{
	CurrentHP -= Damage;
	if (CurrentHP > 0.0F)
	{
		DamageEffect->Activate(true);
	}
	else
	{
		CurrentState = EDarkWarriorStates::DEAD;
		bInAction = true;
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		GetWorldTimerManager().SetTimer(ReloadTimerHandle, this, &ADarkWarriorCharacter::ReloadLevel, 5.0F, false);
	}

}

void ADarkWarriorCharacter::ReloadLevel()
{
	GetWorldTimerManager().ClearTimer(ReloadTimerHandle);
	UGameplayStatics::OpenLevel(GetWorld(), FName(*UGameplayStatics::GetCurrentLevelName(GetWorld())));
}