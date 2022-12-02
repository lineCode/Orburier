// Fill out your copyright notice in the Description page of Project Settings.


#include "Action/OrbAction.h"


static FGameplayTagContainer DefaultContainer = FGameplayTagContainer();

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
