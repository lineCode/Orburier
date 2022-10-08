// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "OrbGameplayTagContainer.generated.h"


struct FGameplayTag;

struct FOrbGameplayTagContainerEntry
{
	int32 Count;
	int32 ExplicitCount;
};

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnOrbGameplayTagContainerEntryChange, const FGameplayTag&, int32);

/**
 * 
 */
USTRUCT(BlueprintType)
struct ORBURIER_API FOrbGameplayTagContainer
{
	GENERATED_BODY()

	/** Constructors */
	FOrbGameplayTagContainer()
	{
	}

	FOrbGameplayTagContainer(FOrbGameplayTagContainer const& Other)
	{
		*this = Other;
	}

	/** Explicit to prevent people from accidentally using the wrong type of operation */
	explicit FOrbGameplayTagContainer(const FGameplayTag& Tag)
	{
		AddTag(Tag);
	}

	FOrbGameplayTagContainer(FOrbGameplayTagContainer&& Other) noexcept
		: GameplayTags(MoveTemp(Other.GameplayTags))
	{

	}

	~FOrbGameplayTagContainer()
	{
	}

	/** Assignment/Equality operators */
	FOrbGameplayTagContainer& operator=(FOrbGameplayTagContainer const& Other);
	FOrbGameplayTagContainer& operator=(FOrbGameplayTagContainer&& Other) noexcept;
	bool operator==(FOrbGameplayTagContainer const& Other) const;
	bool operator!=(FOrbGameplayTagContainer const& Other) const;

	/**
	* Determine if TagToCheck is present in this container, also checking against parent tags
	* {"A.1"}.HasTag("A") will return True, {"A"}.HasTag("A.1") will return False
	* If TagToCheck is not Valid it will always return False
	* 
	* @return True if TagToCheck is in this container, false if it is not
	*/
	FORCEINLINE_DEBUGGABLE bool HasTag(const FGameplayTag& TagToCheck) const
	{
		if (!TagToCheck.IsValid())
			return false;
		
		// Check explicit and parent tag list 
		return GameplayTags.Contains(TagToCheck);
	}
	
	/**
	 * Determine if TagToCheck is explicitly present in this container, only allowing exact matches
	 * {"A.1"}.HasTagExact("A") will return False
	 * If TagToCheck is not Valid it will always return False
	 * 
	 * @return True if TagToCheck is in this container, false if it is not
	 */
	FORCEINLINE_DEBUGGABLE bool HasTagExact(const FGameplayTag& TagToCheck) const
	{
		if (!TagToCheck.IsValid())
			return false;

		const FOrbGameplayTagContainerEntry* TagInfo = GameplayTags.Find(TagToCheck);
		// Only check check explicit tag list
		return TagInfo && TagInfo->ExplicitCount > 0;
	}

	/**
	 * Checks if this container contains ANY of the tags in the specified container, also checks against parent tags
	 * {"A.1"}.HasAny({"A","B"}) will return True, {"A"}.HasAny({"A.1","B"}) will return False
	 * If ContainerToCheck is empty/invalid it will always return False
	 *
	 * @return True if this container has ANY of the tags of in ContainerToCheck
	 */
	FORCEINLINE_DEBUGGABLE bool HasAny(const FGameplayTagContainer& ContainerToCheck) const
	{
		if (ContainerToCheck.IsEmpty())
			return false;
		
		for (const FGameplayTag& OtherTag : ContainerToCheck)
		{
			if (GameplayTags.Contains(OtherTag))
				return true;
		}
		
		return false;
	}
	/**
	* Checks if this container contains ANY (not exact) of the exact tags in the specified container, also checks against parent tags
	* {"A.1"}.HasAny({"A","B"}) will return True, {"A"}.HasAny({"A.1","B"}) will return False
	* If ContainerToCheck is empty/invalid it will always return False
	* ContainerToCheck w
	*
	* @return True if this container has ANY of the tags of in ContainerToCheck
	*/
	bool HasAny(const FOrbGameplayTagContainer& ContainerToCheck) const
	{
		if (ContainerToCheck.IsEmpty())
			return false;
		
		for (TTuple<FGameplayTag, FOrbGameplayTagContainerEntry> OtherTag : ContainerToCheck.GameplayTags)
		{
			if (OtherTag.Value.ExplicitCount > 0 && GameplayTags.Contains(OtherTag.Key))
				return true;
		}
		
		return false;
	}

	/**
	 * Checks if this container contains ANY of the tags in the specified container, only allowing exact matches
	 * {"A.1"}.HasAny({"A","B"}) will return False
	 * If ContainerToCheck is empty/invalid it will always return False
	 *
	 * @return True if this container has ANY of the tags of in ContainerToCheck
	 */
	FORCEINLINE_DEBUGGABLE bool HasAnyExact(const FGameplayTagContainer& ContainerToCheck) const
	{
		if (ContainerToCheck.IsEmpty())
			return false;
		
		for (const FGameplayTag& OtherTag : ContainerToCheck)
		{
			if (const FOrbGameplayTagContainerEntry* TagInfo = GameplayTags.Find(OtherTag); TagInfo && TagInfo->ExplicitCount > 0)
				return true;
		}
		
		return false;
	}
	/**
	* Checks if this container contains ANY of the tags in the specified container, only allowing exact matches
	* {"A.1"}.HasAny({"A","B"}) will return False
	* If ContainerToCheck is empty/invalid it will always return False
	*
	* @return True if this container has ANY of the tags of in ContainerToCheck
	*/
	FORCEINLINE_DEBUGGABLE bool HasAnyExact(const FOrbGameplayTagContainer& ContainerToCheck) const
	{
		if (ContainerToCheck.IsEmpty())
			return false;

		// Only check check explicit tag list
		for (TTuple<FGameplayTag, FOrbGameplayTagContainerEntry> OtherTag : ContainerToCheck.GameplayTags)
		{
			if(OtherTag.Value.ExplicitCount > 0)
			{
				if (const FOrbGameplayTagContainerEntry* TagInfo = GameplayTags.Find(OtherTag.Key); TagInfo && TagInfo->ExplicitCount > 0)
					return true;
			}
		}
		
		return false;
	}

	/**
	 * Checks if this container contains ALL of the tags in the specified container, also checks against parent tags
	 * {"A.1","B.1"}.HasAll({"A","B"}) will return True, {"A","B"}.HasAll({"A.1","B.1"}) will return False
	 * If ContainerToCheck is empty/invalid it will always return True, because there were no failed checks
	 *
	 * @return True if this container has ALL of the tags of in ContainerToCheck, including if ContainerToCheck is empty
	 */
	FORCEINLINE_DEBUGGABLE bool HasAll(const FGameplayTagContainer& ContainerToCheck) const
	{
		if (ContainerToCheck.IsEmpty())
			return true;
		
		for (const FGameplayTag& OtherTag : ContainerToCheck)
		{
			if (!GameplayTags.Contains(OtherTag))
				return false;
		}
		
		return true;
	}
	/**
	* Checks if this container contains ALL of the tags in the specified container, also checks against parent tags
	* {"A.1","B.1"}.HasAll({"A","B"}) will return True, {"A","B"}.HasAll({"A.1","B.1"}) will return False
	* If ContainerToCheck is empty/invalid it will always return True, because there were no failed checks
	*
	* @return True if this container has ALL of the tags of in ContainerToCheck, including if ContainerToCheck is empty
	*/
	FORCEINLINE_DEBUGGABLE bool HasAll(const FOrbGameplayTagContainer& ContainerToCheck) const
	{
		if (ContainerToCheck.IsEmpty())
			return true;
		
		for (TTuple<FGameplayTag, FOrbGameplayTagContainerEntry> OtherTag : ContainerToCheck.GameplayTags)
		{
			if (const FOrbGameplayTagContainerEntry* TagInfo = GameplayTags.Find(OtherTag.Key); !TagInfo)
				return false;
		}
		
		return true;
	}

	/**
	 * Checks if this container contains ALL of the tags in the specified container, only allowing exact matches
	 * {"A.1","B.1"}.HasAll({"A","B"}) will return False
	 * If ContainerToCheck is empty/invalid it will always return True, because there were no failed checks
	 *
	 * @return True if this container has ALL of the tags of in ContainerToCheck, including if ContainerToCheck is empty
	 */
	FORCEINLINE_DEBUGGABLE bool HasAllExact(const FGameplayTagContainer& ContainerToCheck) const
	{
		if (ContainerToCheck.IsEmpty())
			return true;
		
		for (const FGameplayTag& OtherTag : ContainerToCheck)
		{
			if(const FOrbGameplayTagContainerEntry* TagInfo = GameplayTags.Find(OtherTag); !TagInfo || TagInfo->ExplicitCount <= 0)
				return false;
		}
		
		return true;
	}
	/**
	* Checks if this container contains ALL of the tags in the specified container, only allowing exact matches
	* {"A.1","B.1"}.HasAll({"A","B"}) will return False
	* If ContainerToCheck is empty/invalid it will always return True, because there were no failed checks
	*
	* @return True if this container has ALL of the tags of in ContainerToCheck, including if ContainerToCheck is empty
	*/
	FORCEINLINE_DEBUGGABLE bool HasAllExact(const FOrbGameplayTagContainer& ContainerToCheck) const
	{
		if (ContainerToCheck.IsEmpty())
			return true;
		
		for (TTuple<FGameplayTag, FOrbGameplayTagContainerEntry> OtherTag : ContainerToCheck.GameplayTags)
		{
			if(OtherTag.Value.ExplicitCount > 0)
			{
				if (const FOrbGameplayTagContainerEntry* TagInfo = GameplayTags.Find(OtherTag.Key); !TagInfo || TagInfo->ExplicitCount <= 0)
					return false;
			}
		}
		
		return true;
	}

	/** Returns the number of added tag types */
	FORCEINLINE int32 Num() const
	{
		return GameplayTags.Num();
	}

	/** Returns the number of explicitly added tag types */
	FORCEINLINE int32 NumExact() const
	{
		return ExplicitTagTypeCounter;
	}

	/*Returns how many times the tag has been added -> implicitly & explicitly*/
	int32 Num(const FGameplayTag& Tag) const
	{
		const FOrbGameplayTagContainerEntry* TagInfo = GameplayTags.Find(Tag);
		
		return !TagInfo
			? 0
			: TagInfo->Count;
	}

	/*Returns how many times the tag has been explicitly added*/
	int32 NumExact(const FGameplayTag& Tag) const
	{
		const FOrbGameplayTagContainerEntry* TagInfo = GameplayTags.Find(Tag);
		
		return !TagInfo
			? 0
			: TagInfo->ExplicitCount;
	}

	/** Returns whether the container has any valid tags */
	FORCEINLINE bool IsValid() const
	{
		return GameplayTags.Num() > 0;
	}

	/** Returns true if container is empty */
	FORCEINLINE bool IsEmpty() const
	{
		return GameplayTags.Num() == 0;
	}
	
	///**
	// * Returns a filtered version of this container, returns all tags that match against any of the tags in OtherContainer, expanding parents
	// *
	// * @param otherContainer		The Container to filter against
	// *
	// * @return A FGameplayTagContainer containing the filtered tags
	// */
	//FGameplayTagContainer Filter(const FGameplayTagContainer& otherContainer) const;
	///**
	//* Returns a filtered version of this container, returns all tags that match against any of the tags in OtherContainer, expanding parents
	//*
	//* @param otherContainer		The Container to filter against
	//*
	//* @return A FGameplayTagContainer containing the filtered tags
	//*/
	//FGameplayTagContainer Filter(const FOrbGameplayTagContainer& otherContainer) const;
	///**
	//* Returns a filtered version of this container, returns all tags that match against any of the tags in OtherContainer, expanding parents
	//*
	//* @param otherContainer		The Container to filter against
	//*
	//* @return A FGameplayTagContainer containing the filtered tags
	//*/
	//FOrbGameplayTagContainer FilterMulti(const FGameplayTagContainer& otherContainer) const;
	///**
	//* Returns a filtered version of this container, returns all tags that match against any of the tags in OtherContainer, expanding parents
	//*
	//* @param otherContainer		The Container to filter against
	//*
	//* @return A FGameplayTagContainer containing the filtered tags
	//*/
	//FOrbGameplayTagContainer FilterMulti(const FOrbGameplayTagContainer& otherContainer) const;

	///**
	//* Returns a filtered version of this container, returns all tags that match against any of the tags in OtherContainer, expanding parents
	//*
	//* @param otherContainer		The Container to filter against
	//*
	//* @return A FGameplayTagContainer containing the filtered tags
	//*/
	//FGameplayTagContainer FilterExact(const FGameplayTagContainer& otherContainer) const;
	///**
	//* Returns a filtered version of this container, returns all tags that match against any of the tags in OtherContainer, expanding parents
	//*
	//* @param otherContainer		The Container to filter against
	//*
	//* @return A FGameplayTagContainer containing the filtered tags
	//*/
	//FGameplayTagContainer FilterExact(const FOrbGameplayTagContainer& otherContainer) const;
	///**
	//* Returns a filtered version of this container, returns all tags that match against any of the tags in OtherContainer, expanding parents
	//*
	//* @param otherContainer		The Container to filter against
	//*
	//* @return A FGameplayTagContainer containing the filtered tags
	//*/
	//FOrbGameplayTagContainer FilterMultiExact(const FGameplayTagContainer& otherContainer) const;
	///**
	//* Returns a filtered version of this container, returns all tags that match against any of the tags in OtherContainer, expanding parents
	//*
	//* @param otherContainer		The Container to filter against
	//*
	//* @return A FGameplayTagContainer containing the filtered tags
	//*/
	//FOrbGameplayTagContainer FilterMultiExact(const FOrbGameplayTagContainer& otherContainer) const;

	/** 
	 * Adds all the tags from one container to this container 
	 * NOTE: From set theory, this effectively is the union of the container this is called on with Other.
	 *
	 * @param Other TagContainer that has the tags you want to add to this container 
	 */
	void AppendTags(FGameplayTagContainer const& Other);
	/** 
	* Adds all the tags from one container to this container 
	* NOTE: From set theory, this effectively is the union of the container this is called on with Other.
	*
	* @param Other TagContainer that has the tags you want to add to this container 
	*/
	void AppendTags(FOrbGameplayTagContainer const& Other);

	///** 
	// * Adds all the tags that match between the two specified containers to this container.  WARNING: This matches any
	// * parent tag in A, not just exact matches!  So while this should be the union of the container this is called on with
	// * the intersection of OtherA and OtherB, it's not exactly that.  Since OtherB matches against its parents, any tag
	// * in OtherA which has a parent match with a parent of OtherB will count.  For example, if OtherA has Color.Green
	// * and OtherB has Color.Red, that will count as a match due to the Color parent match!
	// * If you want an exact match, you need to call A.FilterExact(B) (above) to get the intersection of A with B.
	// * If you need the disjunctive union (the union of two sets minus their intersection), use AppendTags to create
	// * Union, FilterExact to create Intersection, and then call Union.RemoveTags(Intersection).
	// *
	// * @param otherA TagContainer that has the matching tags you want to add to this container, these tags have their parents expanded
	// * @param otherB TagContainer used to check for matching tags.  If the tag matches on any parent, it counts as a match.
	// */
	//void AppendMatchingTags(FGameplayTagContainer const& otherA, FGameplayTagContainer const& otherB);
	///** 
	//* Adds all the tags that match between the two specified containers to this container.  WARNING: This matches any
	//* parent tag in A, not just exact matches!  So while this should be the union of the container this is called on with
	//* the intersection of OtherA and OtherB, it's not exactly that.  Since OtherB matches against its parents, any tag
	//* in OtherA which has a parent match with a parent of OtherB will count.  For example, if OtherA has Color.Green
	//* and OtherB has Color.Red, that will count as a match due to the Color parent match!
	//* If you want an exact match, you need to call A.FilterExact(B) (above) to get the intersection of A with B.
	//* If you need the disjunctive union (the union of two sets minus their intersection), use AppendTags to create
	//* Union, FilterExact to create Intersection, and then call Union.RemoveTags(Intersection).
	//*
	//* @param otherA TagContainer that has the matching tags you want to add to this container, these tags have their parents expanded
	//* @param otherB TagContainer used to check for matching tags.  If the tag matches on any parent, it counts as a match.
	//*/
	//void AppendMatchingTags(FOrbGameplayTagContainer const& otherA, FGameplayTagContainer const& otherB);
	///** 
	//* Adds all the tags that match between the two specified containers to this container.  WARNING: This matches any
	//* parent tag in A, not just exact matches!  So while this should be the union of the container this is called on with
	//* the intersection of OtherA and OtherB, it's not exactly that.  Since OtherB matches against its parents, any tag
	//* in OtherA which has a parent match with a parent of OtherB will count.  For example, if OtherA has Color.Green
	//* and OtherB has Color.Red, that will count as a match due to the Color parent match!
	//* If you want an exact match, you need to call A.FilterExact(B) (above) to get the intersection of A with B.
	//* If you need the disjunctive union (the union of two sets minus their intersection), use AppendTags to create
	//* Union, FilterExact to create Intersection, and then call Union.RemoveTags(Intersection).
	//*
	//* @param otherA TagContainer that has the matching tags you want to add to this container, these tags have their parents expanded
	//* @param otherB TagContainer used to check for matching tags.  If the tag matches on any parent, it counts as a match.
	//*/
	//void AppendMatchingTags(FGameplayTagContainer const& otherA, FOrbGameplayTagContainer const& otherB);
	///** 
	//* Adds all the tags that match between the two specified containers to this container.  WARNING: This matches any
	//* parent tag in A, not just exact matches!  So while this should be the union of the container this is called on with
	//* the intersection of OtherA and OtherB, it's not exactly that.  Since OtherB matches against its parents, any tag
	//* in OtherA which has a parent match with a parent of OtherB will count.  For example, if OtherA has Color.Green
	//* and OtherB has Color.Red, that will count as a match due to the Color parent match!
	//* If you want an exact match, you need to call A.FilterExact(B) (above) to get the intersection of A with B.
	//* If you need the disjunctive union (the union of two sets minus their intersection), use AppendTags to create
	//* Union, FilterExact to create Intersection, and then call Union.RemoveTags(Intersection).
	//*
	//* @param otherA TagContainer that has the matching tags you want to add to this container, these tags have their parents expanded
	//* @param otherB TagContainer used to check for matching tags.  If the tag matches on any parent, it counts as a match.
	//*/
	//void AppendMatchingTags(FOrbGameplayTagContainer const& otherA, FOrbGameplayTagContainer const& otherB);

	/**
	 * Add the specified tag to the container
	 *
	 * @param TagToAdd Tag to add to the container
	 */
	void AddTag(const FGameplayTag& TagToAdd);

	/**
	 * Tag to remove from the container
	 * 
	 * @param TagToRemove		Tag to remove from the container
	 */
	void RemoveTag(const FGameplayTag& TagToRemove);

	/**
	 * Removes all tags in TagsToRemove from this container
	 *
	 * @param TagsToRemove	Tags to remove from the container
	 */
	void RemoveTags(const FGameplayTagContainer& TagsToRemove);
	/**
	* Removes all tags in TagsToRemove from this container
	*
	* @param TagsToRemove	Tags to remove from the container
	*/
	void RemoveTags(const FOrbGameplayTagContainer& TagsToRemove);

	/** Remove all tags and events from the container. Will maintain slack by default */
	void Reset();

	/** Remove all tags from the container. Will maintain slack by default */
	void Empty();

	/** Returns string version of container in ImportText format */
	FString ToString() const;

	/** Sets from a ImportText string, used in asset registry */
	void FromExportString(const FString& ExportString, int32 PortFlags = 0);

	/** Returns abbreviated human readable Tag list without parens or property names. If bQuoted is true it will quote each tag */
	FString ToStringSimple(bool IsQuoted = false) const;

	/** Returns abbreviated human readable Tag list without parens or property names, but will limit each string to specified len.  This is to get around output restrictions*/
	TArray<FString> ToStringsMaxLen(int32 MaxLen) const;

	/** Returns human readable description of what match is being looked for on the readable tag list. */
	FText ToMatchingText(EGameplayContainerMatchType MatchType, bool bInvertCondition) const;
	

	/** Creates a const iterator for the contents of this array */
	//TMap<FGameplayTag, FOrbGameplayTagContainerEntry>::TConstIterator CreateConstIterator() const
	//{
	//	return GameplayTags.CreateConstIterator();
	//}

	/** Gets a list of the gameplay tags */
	//int32 ToArray(TArray<FGameplayTag>& Array) const
	//{
	//	return GetAsArray(Array, false);
	//}
	
	/** Gets a list of the gameplay tags */
	//int32 ToArrayExact(TArray<FGameplayTag>& Array) const
	//{
	//	return GetAsArray(Array, true);
	//}

	FOnOrbGameplayTagContainerEntryChange& RegisterTagCountChanged() { return OnTagCountChangedDelegate; }
	FOnOrbGameplayTagContainerEntryChange& RegisterExactTagCountChanged() { return OnExactTagCountChangedDelegate; }

	void PauseTagChangedEvent();
	void ContinuePauseTagChangedEvent();
	void SendTagCountStateAsChange();
	bool IsChangedEventPaused() const;

	void Compress();

protected:
	/** Gets a list of the gameplay tags */
	int32 GetAsArray(TArray<FGameplayTag>& Array, const bool IsExact) const
	{
		if(!IsExact)
			return GameplayTags.GetKeys(Array);

		Array.Reset();
		for (const TTuple<FGameplayTag, FOrbGameplayTagContainerEntry>& GameplayTag : GameplayTags)
		{
			if(GameplayTag.Value.ExplicitCount > 0)
				Array.Add(GameplayTag.Key);
		}

		return Array.Num();
	}
	
	/**
	* Add the specified tag to the container
	*
	* @param TagToAdd Tag to add to the container
	* @param ExplicitCount Number that should be added to the tag count (explicit -> implicit will be added accordingly by the function)
	*/
	void AddTag(const FGameplayTag& TagToAdd, int32 ExplicitCount);
	void AddTagToMap(const FGameplayTag& TagToAdd, int32 Count, bool IsExplicit);

	/**
	* Tag to remove from the container
	* 
	* @param TagToRemove		Tag to remove from the container
	* @param ExplicitCount		Number that should be removed from the tag count (explicit -> implicit will be removed accordingly by the function)
	*/
	void RemoveTag(const FGameplayTag& TagToRemove, int32 ExplicitCount);
	int32 RemoveTagFromMap(const FGameplayTag& TagToRemove, int32 Count, bool IsExplicit);

	bool TagMatchesAny(const FGameplayTag& TagToCheck) const;
	bool TagMatchesAnyExact(const FGameplayTag& TagToCheck) const;

	/** Map of gameplay tags */
	TMap<FGameplayTag, FOrbGameplayTagContainerEntry> GameplayTags;

	bool IsGameplayTagsMapDirty = false;
	bool IsTagCountChangedEventPaused = false;
	int32 ExplicitTagTypeCounter = 0;
	
	/** Delegate fired whenever any tag's count changes to or away from zero */
	FOnOrbGameplayTagContainerEntryChange OnTagCountChangedDelegate;
	FOnOrbGameplayTagContainerEntryChange OnExactTagCountChangedDelegate;
};
