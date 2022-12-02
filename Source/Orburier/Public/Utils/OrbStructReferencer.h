// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "OrbStructReferencer.generated.h"


USTRUCT()
struct FMyStruct
{
	GENERATED_BODY()
	
};

/**
 * 
 */
UCLASS()
class ORBURIER_API UOrbStructReferencer : public UObject
{
	GENERATED_BODY()

public:
    template<typename T>
	void Set(T* structReference)
    {
    	
    	//TODO: Other condition than with editor?
#if WITH_EDITOR
        {
        	auto type = GetType();
        	check(type != nullptr)
        	check(structReference->StaticStruct() == type)
        }
#endif
    	
    	Struct = structReference;
    }

	UFUNCTION()
	virtual UScriptStruct* GetType() const
    {
	    check(false)
    	return nullptr;
    }

	void* Get() { return Struct; }
	
protected:
	void* Struct;
};
	