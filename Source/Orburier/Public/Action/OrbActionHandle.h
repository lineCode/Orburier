// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OrbActionHandle.generated.h"

USTRUCT()
struct ORBURIER_API FOrbActionHandle
{
	GENERATED_BODY()

	FOrbActionHandle()
		: FOrbActionHandle(0)
	{ }
	
	FOrbActionHandle(int32 handle)
		: Handle(handle)
	{ }
	
private:
	int32 Handle;
};
