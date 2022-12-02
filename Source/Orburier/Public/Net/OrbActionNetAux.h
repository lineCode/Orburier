// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "OrbActionNetAux.generated.h"

struct FNetSerializeParams;
/**
 * 
 */
USTRUCT()
struct ORBURIER_API FOrbActionNetAux
{
	GENERATED_BODY()
	
	void NetSerialize(const FNetSerializeParams& P) { }

	void ToString(FAnsiStringBuilderBase& Out) const
	{ /*TODO*/ }
	
	void Interpolate(const FOrbActionNetAux* From, const FOrbActionNetAux* To, float PCT)
	{ /*TODO*/ }
	
	bool ShouldReconcile(const FOrbActionNetAux& AuthorityState) const { return false; /*TODO*/ }
};
