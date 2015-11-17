// Fill out your copyright notice in the Description page of Project Settings.

#include "LOCExample.h"
#include "MyUserWidget.h"


void UMyUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	/// NOTE: ���� NSLOCTEXT()�� Key�� �ʱ� ������ ���ǰ� ���� ����
	///		  Literal �������� �ؽ�Ʈ�� ã�� �ȴٰ� �� -_-;;;

					//NSLOCTEXT(Namespace,			Key,		Literal)
	LevelText		= NSLOCTEXT("CharacterInfo",	"Level",	"LV2");
	SkillText		= NSLOCTEXT("CharacterInfo",	"Skill",	"Skill");
	InvenText		= NSLOCTEXT("CharacterInfo",	"Inven",	"Inven");
	RubyShopText	= NSLOCTEXT("CharacterInfo",	"RubyShop",	"RubyShop");
	RankingText		= NSLOCTEXT("CharacterInfo",	"Ranking",	"Ranking");
	MissionText		= NSLOCTEXT("CharacterInfo",	"Mission",	"Mission");
	EnterText		= NSLOCTEXT("CharacterInfo",	"Enter",	"Enter");
	GambleText		= NSLOCTEXT("CharacterInfo",	"Gamble",	"Gamble");
}

