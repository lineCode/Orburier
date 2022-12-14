// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "OrbActionHandle.h"
#include "UObject/Object.h"
#include "Utils/OrbTimeState.h"
#include "OrbAction.generated.h"


UENUM(BlueprintType)
enum class EOrbInstancingPolicy : uint8
{
	/* All SystemComponents use the same Instance */
	Shared			UMETA(DisplayName="Shared"),
	/* All SystemComponents create their own Instances */
	Instanced 		UMETA(DisplayName="Instanced"),

	MAX				UMETA(Hidden)
};

UENUM(BlueprintType)
enum class EOrbAvailabilityPolicy : uint8
{
	/* ActionBlock is always available for activation */
	Public			UMETA(DisplayName="Public"),
	/* ActionBlock needs to be granted before the activation is available */
	Granted 		UMETA(DisplayName="Granted"),

	MAX				UMETA(Hidden)
};

UENUM(BlueprintType)
enum class EOrbReActivationPolicy : uint8
{
	/* Activating the ActionBlock while its already running is not possible */
	NotAllowed		UMETA(DisplayName="NotAllowed"),
	/* ActionBlock can be activated again while running. OnActionBlockStart will be Executed */
	Allowed 		UMETA(DisplayName="Allowed"),
	/* ActionBlock can be activated again while running. OnActionBlockStart wont be Executed */
	SilentAllowed	UMETA(DisplayName="SilentAllowed"),

	MAX				UMETA(Hidden)
};

UENUM(BlueprintType)
enum class EOrbActivityPolicy : uint8
{
	/* Needs to be activated */
	Active			UMETA(DisplayName="Active"),
	/* Is active when granted (Public ActionBlocks will not be applied) */
	Passive			UMETA(DisplayName="Passive"),
	/* Needs to be activated & ends after one tick automatically */
	OneTick 		UMETA(DisplayName="OneTick"),

	MAX				UMETA(Hidden)
};


class UOrbAction;

USTRUCT()
struct ORBURIER_API FOrbActionStateHandler
{
	GENERATED_BODY()

	FOrbActionHandle Handle;
};

struct ORBURIER_API FOrbActionAttributeAccessor
{
protected:
	void ConfigureBase(UOrbAction* owner);

	FOrbActionStateHandler& GetStateHandler();
	
private:
	FOrbActionHandle OwnerHandle;
	TWeakObjectPtr<UOrbAction> OwnerPtr;

	void RestoreOwnerPtr();
};

template<typename AttributeType>
struct ORBURIER_API TOrbActionAttributeRead : FOrbActionAttributeAccessor
{
public:
	void Configure(UOrbAction* owner)
	{
		ConfigureBase(owner);
	}

	AttributeType* Get()
	{
		return nullptr;
	}
};

template<typename AttributeType>
struct ORBURIER_API TOrbActionAttributeWrite : FOrbActionAttributeAccessor
{
public:
	void Configure(UOrbAction* owner)
	{
		ConfigureBase(owner);
	}

	AttributeType* Get()
	{
		return nullptr;
	}
};


/**
 * 
 */
UCLASS()
class ORBURIER_API UOrbAction : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION()
	virtual EOrbInstancingPolicy GetInstancingPolicy() const { return EOrbInstancingPolicy::Shared; };

	UFUNCTION()
	virtual EOrbAvailabilityPolicy GetAvailabilityPolicy() const { return EOrbAvailabilityPolicy::Granted; }

	UFUNCTION()
	virtual EOrbReActivationPolicy GetReActivationPolicy() const { return EOrbReActivationPolicy::NotAllowed; }

	UFUNCTION()
	virtual EOrbActivityPolicy GetActivityPolicy() const { return EOrbActivityPolicy::Active; }

	virtual const FGameplayTagContainer* GetActionTags() const;

	virtual const FGameplayTagContainer* GetCancelActionsWithTag() const;
	
	virtual const FGameplayTagContainer* GetBlockActionsWithTag() const;

	virtual const FGameplayTagContainer* GetActivationOwnedTags() const;
    	
	virtual const FGameplayTagContainer* GetActivationRequiredTags() const;

	virtual const FGameplayTagContainer* GetActivationBlockedTags() const;

	virtual void Configure();

	virtual bool CanActivate(const FOrbTimeState& TimeState, bool isExternal) { return false; }
	
	virtual bool CanDeactivate(const FOrbTimeState& TimeState, bool isExternal) { return false; }

	virtual void OnActivate(const FOrbTimeStep& TimeStep) { }

	virtual void OnDeactivate(const FOrbTimeStep& TimeStep, const FOrbTime& ActivationTime) { }

	virtual void OnSimulate(const FOrbTimeStep& TimeStep, const FOrbTime& ActivationTime) { }
	
	virtual void OnEffect(const FOrbTimeState& TimeStep, const FOrbTime& ActivationTime, bool isReconcile) { }

protected:
	TOrbActionAttributeWrite<FOrbActionStateHandler> WriteConfig;
	
private:
	FOrbActionStateHandler Configuration;

	friend TOrbActionAttributeRead;
	friend TOrbActionAttributeWrite;
	friend FOrbActionAttributeAccessor;
};
