// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OrbActionNetSync.generated.h"

struct FNetSerializeParams;
/**
 * 
 */
USTRUCT()
struct ORBURIER_API FOrbActionNetSync
{
	GENERATED_BODY()
	
	void NetSerialize(const FNetSerializeParams& P) { }

	void ToString(FAnsiStringBuilderBase& Out) const
	{ /*TODO*/ }
	
	void Interpolate(const FOrbActionNetSync* From, const FOrbActionNetSync* To, float PCT)
	{ /*TODO*/ }
	
	bool ShouldReconcile(const FOrbActionNetSync& AuthorityState) const { return false; /*TODO*/ }
};
