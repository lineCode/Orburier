// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OrbActionNetInput.generated.h"

struct FNetSerializeParams;
/**
 * 
 */
USTRUCT()
struct ORBURIER_API FOrbActionNetInput
{
	GENERATED_BODY()

	void NetSerialize(const FNetSerializeParams& P) { }

	void ToString(FAnsiStringBuilderBase& Out) const
	{ /*TODO*/ }
	
	void Interpolate(const FOrbActionNetInput* From, const FOrbActionNetInput* To, float PCT)
	{ /*TODO*/ }
	
	bool ShouldReconcile(const FOrbActionNetInput& AuthorityState) const { return false; /*TODO*/ }
};
