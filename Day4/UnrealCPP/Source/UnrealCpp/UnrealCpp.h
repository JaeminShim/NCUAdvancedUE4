// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"

#define print(x) GEngine->AddOnScreenDebugMessage(0, 3.0F, FColor::Cyan, x)

DECLARE_LOG_CATEGORY_EXTERN(HttpLog, Log, All);
