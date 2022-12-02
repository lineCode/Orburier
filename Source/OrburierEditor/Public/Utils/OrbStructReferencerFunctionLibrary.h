// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "OrbStructReferencerFunctionLibrary.generated.h"

class UOrbStructReferencer;
/**
 * 
 */
UCLASS()
class ORBURIEREDITOR_API UOrbStructReferencerFunctionLibrary : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
		static bool SetFloatByName(UOrbStructReferencer* Target, FName VarName, float NewValue, float &OutValue);

	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
		static bool SetIntByName(UOrbStructReferencer* Target, FName VarName, int NewValue, int &OutValue);
	
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
		static bool SetBoolByName(UOrbStructReferencer* Target, FName VarName, bool NewValue, bool &OutValue);

	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
		static bool SetNameByName(UOrbStructReferencer* Target, FName VarName, FName NewValue, FName &OutValue);

	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
		static bool SetObjectByName(UOrbStructReferencer* Target, FName VarName, UObject* NewValue, UObject* &OutValue);

	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
		static bool SetClassByName(UOrbStructReferencer* Target, FName VarName, class UClass* NewValue, class UClass* &OutValue);

	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
		static bool SetByteByName(UOrbStructReferencer* Target, FName VarName, uint8 NewValue, uint8 &OutValue);

	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
		static bool SetStringByName(UOrbStructReferencer* Target, FName VarName, FString NewValue, FString &OutValue);

	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
		static bool SetTextByName(UOrbStructReferencer* Target, FName VarName, FText NewValue, FText &OutValue);

	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
		static bool SetStructByName(UOrbStructReferencer* Target, FName VarName, UScriptStruct* NewValue, UScriptStruct* &OutValue);

	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
		static bool SetEnumByName(UOrbStructReferencer* Target, FName VarName, uint8 NewValue, uint8 &OutValue);

	//Getters
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
		static bool GetFloatByName(UOrbStructReferencer* Target, FName VarName, float &OutValue);

	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
		static bool GetIntByName(UOrbStructReferencer* Target, FName VarName, int &OutValue);

	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
		static bool GetBoolByName(UOrbStructReferencer* Target, FName VarName, bool &OutValue);

	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
		static bool GetNameByName(UOrbStructReferencer* Target, FName VarName, FName &OutValue);

	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
		static bool GetObjectByName(UOrbStructReferencer* Target, FName VarName, UObject* &OutValue);

	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
		static bool GetClassByName(UOrbStructReferencer* Target, FName VarName, class UClass* &OutValue);

	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
		static bool GetByteByName(UOrbStructReferencer* Target, FName VarName, uint8 &OutValue);

	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
		static bool GetStringByName(UOrbStructReferencer* Target, FName VarName, FString &OutValue);

	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
		static bool GetTextByName(UOrbStructReferencer* Target, FName VarName, FText &OutValue);

	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
		static bool GetStructByName(UOrbStructReferencer* Target, FName VarName, UScriptStruct* &OutValue);

	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
		static bool GetEnumByName(UOrbStructReferencer* Target, FName VarName, uint8 &OutValue);
};
