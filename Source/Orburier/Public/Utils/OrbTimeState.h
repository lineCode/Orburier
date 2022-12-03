// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

typedef int32 FOrbTime;
typedef int32 FOrbFrame;

USTRUCT()
struct ORBURIER_API FOrbTimeState
{
	GENERATED_BODY()
	
	FOrbTime TimeStamp;
	FOrbFrame Frame;
};

USTRUCT()
struct ORBURIER_API FOrbTimeStep : FOrbTimeState
{
	GENERATED_BODY()
	
	FOrbTime DeltaMS;
};
