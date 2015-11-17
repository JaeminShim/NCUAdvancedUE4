// Fill out your copyright notice in the Description page of Project Settings.

#include "LOCExample.h"
#include "MyUserWidget.h"


void UMyUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	/// NOTE: 현재 NSLOCTEXT()의 Key는 초기 설계대로 사용되고 있지 않음
	///		  Literal 기준으로 텍스트를 찾게 된다고 함 -_-;;;

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

