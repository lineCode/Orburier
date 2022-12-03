// Fill out your copyright notice in the Description page of Project Settings.


#include "Action/OrbAction.h"

#include "Utils/OrburierLogging.h"


static FGameplayTagContainer DefaultContainer = FGameplayTagContainer();

void FOrbActionAttributeAccessor::ConfigureBase(UOrbAction* owner)
{
	OwnerHandle = owner->Configuration.Handle;
	OwnerPtr = TWeakObjectPtr<UOrbAction>(owner);
}

FOrbActionStateHandler& FOrbActionAttributeAccessor::GetStateHandler()
{
	if(!OwnerPtr.IsValid())
		RestoreOwnerPtr();

	return OwnerPtr->Configuration;
}

void FOrbActionAttributeAccessor::RestoreOwnerPtr()
{
	UE_LOG(OrburierLog, Error, TEXT("FATAL: Ownerpointer recovery is not yet implemented!"))
	check(false)
}

const FGameplayTagContainer* UOrbAction::GetActionTags() const
{
	return &DefaultContainer;
}

const FGameplayTagContainer* UOrbAction::GetCancelActionsWithTag() const
{
	return &DefaultContainer;
}

const FGameplayTagContainer* UOrbAction::GetBlockActionsWithTag() const
{
	return &DefaultContainer;
}

const FGameplayTagContainer* UOrbAction::GetActivationOwnedTags() const
{
	return &DefaultContainer;
}

const FGameplayTagContainer* UOrbAction::GetActivationRequiredTags() const
{
	return &DefaultContainer;
}

const FGameplayTagContainer* UOrbAction::GetActivationBlockedTags() const
{
	return &DefaultContainer;
}

void UOrbAction::Configure()
{
}
