// Fill out your copyright notice in the Description page of Project Settings.


#include "Utils/OrbStructReferencerFunctionLibrary.h"

#include "Utils/OrbStructReferencer.h"

bool UOrbStructReferencerFunctionLibrary::SetFloatByName(UOrbStructReferencer* Target, FName VarName, float NewValue, float & OutValue)
{
	if (Target)
	{
		if(auto targetStruct = Target->Get())
		{
			float FoundValue;
			FFloatProperty* ValueProp = FindFProperty<FFloatProperty>(Target->GetType(), VarName);
			if (ValueProp)
			{
				ValueProp->SetPropertyValue_InContainer(targetStruct, NewValue); //this actually sets the variable
				FoundValue = ValueProp->GetPropertyValue_InContainer(targetStruct);
				OutValue = FoundValue;
				return true;
			}
		}
	}
	return false;
}

bool UOrbStructReferencerFunctionLibrary::SetIntByName(UOrbStructReferencer * Target, FName VarName, int NewValue, int & OutValue)
{
	if (Target)
	{
		if(auto targetStruct = Target->Get())
		{
			int FoundValue;
			FIntProperty* ValueProp = FindFProperty<FIntProperty>(Target->GetType(), VarName);
			if (ValueProp)
			{
				ValueProp->SetPropertyValue_InContainer(targetStruct, NewValue); //this actually sets the variable
				FoundValue = ValueProp->GetPropertyValue_InContainer(targetStruct);
				OutValue = FoundValue;
				return true;
			}
		}
	}
	return false;
}

bool UOrbStructReferencerFunctionLibrary::SetBoolByName(UOrbStructReferencer * Target, FName VarName, bool NewValue, bool & OutValue)
{
	if (Target)
	{
		if(auto targetStruct = Target->Get())
		{
			bool FoundValue;
			FBoolProperty* ValueProp = FindFProperty<FBoolProperty>(Target->GetType(), VarName);
			if (ValueProp)
			{
				ValueProp->SetPropertyValue_InContainer(targetStruct, NewValue); //this actually sets the variable
				FoundValue = ValueProp->GetPropertyValue_InContainer(targetStruct);
				OutValue = FoundValue;
				return true;
			}
		}
	}
	return false;
}

bool UOrbStructReferencerFunctionLibrary::SetNameByName(UOrbStructReferencer * Target, FName VarName, FName NewValue, FName & OutValue)
{
	if (Target)
	{
		if(auto targetStruct = Target->Get())
		{
			FName FoundValue;
			FNameProperty* ValueProp = FindFProperty<FNameProperty>(Target->GetType(), VarName);
			if (ValueProp)
			{
				ValueProp->SetPropertyValue_InContainer(targetStruct, NewValue); //this actually sets the variable
				FoundValue = ValueProp->GetPropertyValue_InContainer(targetStruct);
				OutValue = FoundValue;
				return true;
			}
		}
	}
	return false;
}

bool UOrbStructReferencerFunctionLibrary::SetObjectByName(UOrbStructReferencer * Target, FName VarName, UObject* NewValue, UObject* & OutValue)
{
	if (Target)
	{
		if(auto targetStruct = Target->Get())
		{
			UObject* FoundValue = nullptr;
			FObjectProperty* ValueProp = FindFProperty<FObjectProperty>(Target->GetType(), VarName);
			if (ValueProp)
			{
				ValueProp->SetPropertyValue_InContainer(targetStruct, NewValue); //this actually sets the variable
				FoundValue = ValueProp->GetPropertyValue_InContainer(targetStruct);
				OutValue = FoundValue;
				return true;
			}
		}
	}
	return false;
}

bool UOrbStructReferencerFunctionLibrary::SetClassByName(UOrbStructReferencer * Target, FName VarName, class UClass* NewValue, class UClass* & OutValue)
{
	//Probably some weirdness to do here
	/*
	if (Target)
	{
		class UClass FoundValue;
		UClassProperty* ValueProp = FindFProperty<UClassProperty>(Target->GetClass(), VarName);
		if (ValueProp)
		{
			ValueProp->SetPropertyValue_InContainer(Target, NewValue); //this actually sets the variable
			FoundValue = ValueProp->GetPropertyValue_InContainer(Target);
			OutValue = FoundValue;
			return true;
		}
	}
	*/
	return false;
}

bool UOrbStructReferencerFunctionLibrary::SetByteByName(UOrbStructReferencer * Target, FName VarName, uint8 NewValue, uint8 & OutValue)
{
	if (Target)
	{
		if(auto targetStruct = Target->Get())
		{
			uint8 FoundValue;
			FByteProperty* ValueProp = FindFProperty<FByteProperty>(Target->GetType(), VarName);
			if (ValueProp)
			{
				ValueProp->SetPropertyValue_InContainer(targetStruct, NewValue); //this actually sets the variable
				FoundValue = ValueProp->GetPropertyValue_InContainer(targetStruct);
				OutValue = FoundValue;
				return true;
			}
		}
	}
	return false;
}

bool UOrbStructReferencerFunctionLibrary::SetStringByName(UOrbStructReferencer * Target, FName VarName, FString NewValue, FString & OutValue)
{
	if (Target)
	{
		if(auto targetStruct = Target->Get())
		{
			FString FoundValue;
			FStrProperty* ValueProp = FindFProperty<FStrProperty>(Target->GetType(), VarName);
			if (ValueProp)
			{
				ValueProp->SetPropertyValue_InContainer(targetStruct, NewValue); //this actually sets the variable
				FoundValue = ValueProp->GetPropertyValue_InContainer(targetStruct);
				OutValue = FoundValue;
				return true;
			}
		}
	}
	return false;
}

bool UOrbStructReferencerFunctionLibrary::SetTextByName(UOrbStructReferencer * Target, FName VarName, FText NewValue, FText & OutValue)
{
	if (Target)
	{
		if(auto targetStruct = Target->Get())
		{
			FText FoundValue;
			FTextProperty* ValueProp = FindFProperty<FTextProperty>(Target->GetType(), VarName);
			if (ValueProp)
			{
				ValueProp->SetPropertyValue_InContainer(targetStruct, NewValue); //this actually sets the variable
				FoundValue = ValueProp->GetPropertyValue_InContainer(targetStruct);
				OutValue = FoundValue;
				return true;
			}
		}
	}
	return false;
}

bool UOrbStructReferencerFunctionLibrary::SetStructByName(UOrbStructReferencer * Target, FName VarName, UScriptStruct* NewValue, UScriptStruct* & OutValue)
{
	//This will need to iterate and shit
	/*
	if (Target)
	{
		UScriptStruct* FoundValue;
		UStructProperty* ValueProp = FindFProperty<UStructProperty>(Target->GetClass(), VarName);
		if (ValueProp)
		{
			ValueProp->SetPropertyValue_InContainer(Target, NewValue); //this actually sets the variable
			FoundValue = ValueProp->GetPropertyValue_InContainer(Target);
			OutValue = FoundValue;
			return true;
		}
	}
	*/
	return false;
}

bool UOrbStructReferencerFunctionLibrary::SetEnumByName(UOrbStructReferencer * Target, FName VarName, uint8 NewValue, uint8 & OutValue)
{
	//Some kind of magic here i guess
	/*
	if (Target)
	{
		uint8 FoundValue;
		UEnumProperty* ValueProp = FindFProperty<UEnumProperty>(Target->GetClass(), VarName);
		if (ValueProp)
		{
			ValueProp->SetPropertyValue_InContainer(Target, NewValue); //this actually sets the variable
			FoundValue = ValueProp->GetPropertyValue_InContainer(Target);
			OutValue = FoundValue;
			return true;
		}
	}
	*/
	return false;
}

//Getters

bool UOrbStructReferencerFunctionLibrary::GetFloatByName(UOrbStructReferencer * Target, FName VarName, float & OutValue)
{
	if (Target) //make sure Target was set in blueprints. 
	{
		if(auto targetStruct = Target->Get())
		{
			float FoundValue;
			FFloatProperty* ValueProp = FindFProperty<FFloatProperty>(Target->GetType(), VarName);  // try to find float property in Target named VarName
			if (ValueProp) //if we found variable
			{
				FoundValue = ValueProp->GetPropertyValue_InContainer(targetStruct);  // get the value from FloatProp
				OutValue = FoundValue;  // return float
				return true; // we can return
			}
		}
	}
	return false; // we haven't found variable return false
}

bool UOrbStructReferencerFunctionLibrary::GetIntByName(UOrbStructReferencer * Target, FName VarName, int & OutValue)
{
	if (Target) //make sure Target was set in blueprints. 
	{
		if(auto targetStruct = Target->Get())
		{
			int FoundValue;
			FIntProperty* ValueProp = FindFProperty<FIntProperty>(Target->GetType(), VarName);  // try to find float property in Target named VarName
			if (ValueProp) //if we found variable
			{
				FoundValue = ValueProp->GetPropertyValue_InContainer(targetStruct);  // get the value from FloatProp
				OutValue = FoundValue;  // return float
				return true; // we can return
			}
		}
	}
	return false; // we haven't found variable return false
}

bool UOrbStructReferencerFunctionLibrary::GetBoolByName(UOrbStructReferencer * Target, FName VarName, bool &OutValue)
{
	if (Target) //make sure Target was set in blueprints. 
	{
		if(auto targetStruct = Target->Get())
		{
			bool FoundValue;
			FBoolProperty* ValueProp = FindFProperty<FBoolProperty>(Target->GetType(), VarName);  // try to find float property in Target named VarName
			if (ValueProp) //if we found variable
			{
				FoundValue = ValueProp->GetPropertyValue_InContainer(targetStruct);  // get the value from FloatProp
				OutValue = FoundValue;  // return float
				return true; // we can return
			}
		}
	}
	return false; // we haven't found variable return false
}

bool UOrbStructReferencerFunctionLibrary::GetNameByName(UOrbStructReferencer * Target, FName VarName, FName & OutValue)
{
	if (Target) //make sure Target was set in blueprints. 
	{
		if(auto targetStruct = Target->Get())
		{
			FName FoundValue;
			FNameProperty* ValueProp = FindFProperty<FNameProperty>(Target->GetType(), VarName);  // try to find float property in Target named VarName
			if (ValueProp) //if we found variable
			{
				FoundValue = ValueProp->GetPropertyValue_InContainer(targetStruct);  // get the value from FloatProp
				OutValue = FoundValue;  // return float
				return true; // we can return
			}
		}
	}
	return false; // we haven't found variable return false
}

bool UOrbStructReferencerFunctionLibrary::GetObjectByName(UOrbStructReferencer * Target, FName VarName, UObject *& OutValue)
{
	if (Target) //make sure Target was set in blueprints. 
	{
		if(auto targetStruct = Target->Get())
		{
			UObject* FoundValue;
			FObjectProperty* ValueProp = FindFProperty<FObjectProperty>(Target->GetType(), VarName);  // try to find float property in Target named VarName
			if (ValueProp) //if we found variable
			{
				FoundValue = ValueProp->GetPropertyValue_InContainer(targetStruct);  // get the value from FloatProp
				OutValue = FoundValue;  // return float
				return true; // we can return
			}
		}
	}
	return false; // we haven't found variable return false
}

bool UOrbStructReferencerFunctionLibrary::GetClassByName(UOrbStructReferencer * Target, FName VarName, UClass *& OutValue)
{
	if (Target) //make sure Target was set in blueprints. 
	{
		if(auto targetStruct = Target->Get())
		{
			UClass* FoundValue;
			FClassProperty* ValueProp = FindFProperty<FClassProperty>(Target->GetType(), VarName);  // try to find float property in Target named VarName
			if (ValueProp) //if we found variable
			{
				FoundValue = ValueProp->GetPropertyValue_InContainer(targetStruct)->StaticClass();  // get the value from FloatProp
				OutValue = FoundValue;  // return float
				return true; // we can return
			}
		}
	}
	return false; // we haven't found variable return false
}

bool UOrbStructReferencerFunctionLibrary::GetByteByName(UOrbStructReferencer * Target, FName VarName, uint8 & OutValue)
{
	if (Target) //make sure Target was set in blueprints. 
	{
		if(auto targetStruct = Target->Get())
		{
			uint8 FoundValue;
			FInt8Property* ValueProp = FindFProperty<FInt8Property>(Target->GetType(), VarName);  // try to find float property in Target named VarName
			if (ValueProp) //if we found variable
			{
				FoundValue = ValueProp->GetPropertyValue_InContainer(targetStruct);  // get the value from FloatProp
				OutValue = FoundValue;  // return float
				return true; // we can return
			}
		}
	}
	return false; // we haven't found variable return false
}

bool UOrbStructReferencerFunctionLibrary::GetStringByName(UOrbStructReferencer * Target, FName VarName, FString & OutValue)
{
	if (Target) //make sure Target was set in blueprints. 
	{
		if(auto targetStruct = Target->Get())
		{
			FString FoundValue;
			FStrProperty* ValueProp = FindFProperty<FStrProperty>(Target->GetType(), VarName);  // try to find float property in Target named VarName
			if (ValueProp) //if we found variable
				{
				FoundValue = ValueProp->GetPropertyValue_InContainer(targetStruct);  // get the value from FloatProp
				OutValue = FoundValue;  // return float
				return true; // we can return
				}
		}
	}
	return false; // we haven't found variable return false
}

bool UOrbStructReferencerFunctionLibrary::GetTextByName(UOrbStructReferencer * Target, FName VarName, FText & OutValue)
{
	if (Target) //make sure Target was set in blueprints. 
	{
		if(auto targetStruct = Target->Get())
		{
			FText FoundValue;
			FTextProperty* ValueProp = FindFProperty<FTextProperty>(Target->GetType(), VarName);  // try to find float property in Target named VarName
			if (ValueProp) //if we found variable
				{
				FoundValue = ValueProp->GetPropertyValue_InContainer(targetStruct);  // get the value from FloatProp
				OutValue = FoundValue;  // return float
				return true; // we can return
				}
		}
	}
	return false; // we haven't found variable return false
}

bool UOrbStructReferencerFunctionLibrary::GetStructByName(UOrbStructReferencer * Target, FName VarName, UScriptStruct *& OutValue)
{
	/*
	if (Target) //make sure Target was set in blueprints. 
	{
		UScriptStruct* FoundValue;
		UStructProperty* ValueProp = FindFProperty<UStructProperty>(Target->GetClass(), VarName);  // try to find float property in Target named VarName
		if (ValueProp) //if we found variable
		{
			FoundValue = ValueProp->GetPropertyValue_InContainer(Target);  // get the value from FloatProp
			OutValue = FoundValue;  // return float
			return true; // we can return
		}
	}
	*/
	return false; // we haven't found variable return false
}

bool UOrbStructReferencerFunctionLibrary::GetEnumByName(UOrbStructReferencer * Target, FName VarName, uint8 & OutValue)
{
	/*
	if (Target) //make sure Target was set in blueprints. 
	{
		float FoundValue;
		UEnumProperty* ValueProp = FindFProperty<UEnumProperty>(Target->GetClass(), VarName);  // try to find float property in Target named VarName
		if (ValueProp) //if we found variable
		{
			FoundValue = ValueProp->GetPropertyValue_InContainer(Target);  // get the value from FloatProp
			OutValue = FoundValue;  // return float
			return true; // we can return
		}
	}
	*/
	return false; // we haven't found variable return false
}