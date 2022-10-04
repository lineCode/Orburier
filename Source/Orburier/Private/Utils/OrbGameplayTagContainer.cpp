// Fill out your copyright notice in the Description page of Project Settings.


#include "Utils/OrbGameplayTagContainer.h"
#include "GameplayTagsManager.h"
#include "Misc/OutputDeviceNull.h"


DECLARE_CYCLE_STAT(TEXT("FOrbGameplayTagContainer::Filter"), STAT_FOrbGameplayTagContainer_Filter, STATGROUP_GameplayTags);

FOrbGameplayTagContainer& FOrbGameplayTagContainer::operator=(FOrbGameplayTagContainer const& other)
{
	// Guard against self-assignment
	if (this == &other)
	{
		return *this;
	}
	GameplayTags.Empty(other.GameplayTags.Num());
	GameplayTags.Append(other.GameplayTags);

	return *this;
}

FOrbGameplayTagContainer& FOrbGameplayTagContainer::operator=(FOrbGameplayTagContainer&& other) noexcept
{
	GameplayTags = MoveTemp(other.GameplayTags);
	return *this;
}

bool FOrbGameplayTagContainer::operator==(FOrbGameplayTagContainer const& other) const
{
	// This is to handle the case where the two containers are in different orders
	if (GameplayTags.Num() != other.GameplayTags.Num())
	{
		return false;
	}

	for (const TTuple<FGameplayTag, FOrbGameplayTagContainerEntry>& tag : other)
	{
		if (!TagMatchesAnyExact(tag.Key))
		{
			return false;
		}
	}

	return true;
}

bool FOrbGameplayTagContainer::operator!=(FOrbGameplayTagContainer const& other) const
{
	return !operator==(other);
}

FGameplayTagContainer FOrbGameplayTagContainer::Filter(const FGameplayTagContainer& otherContainer) const
{
	SCOPE_CYCLE_COUNTER(STAT_FOrbGameplayTagContainer_Filter);

	FGameplayTagContainer resultContainer;

	for (const TTuple<FGameplayTag, FOrbGameplayTagContainerEntry>& tag : GameplayTags)
	{
		if (tag.Key.MatchesAny(otherContainer))
		{
			resultContainer.AddTagFast(tag.Key);
		}
	}

	return resultContainer;
}

FGameplayTagContainer FOrbGameplayTagContainer::Filter(const FOrbGameplayTagContainer& otherContainer) const
{
	SCOPE_CYCLE_COUNTER(STAT_FOrbGameplayTagContainer_Filter);

	FGameplayTagContainer resultContainer;

	for (const TTuple<FGameplayTag, FOrbGameplayTagContainerEntry>& tag : otherContainer)
	{
		if (TagMatchesAny(tag.Key))
		{
			resultContainer.AddTagFast(tag.Key);
		}
	}

	return resultContainer;
}

FOrbGameplayTagContainer FOrbGameplayTagContainer::FilterMulti(const FGameplayTagContainer& otherContainer) const
{
	SCOPE_CYCLE_COUNTER(STAT_FOrbGameplayTagContainer_Filter);

	FOrbGameplayTagContainer resultContainer;

	for (const TTuple<FGameplayTag, FOrbGameplayTagContainerEntry>& tag : GameplayTags)
	{
		if (tag.Key.MatchesAny(otherContainer))
		{
			FOrbGameplayTagContainerEntry infoCopy = tag.Value;
			resultContainer.GameplayTags.Add(tag.Key, infoCopy);
		}
	}

	return resultContainer;
}

FOrbGameplayTagContainer FOrbGameplayTagContainer::FilterMulti(const FOrbGameplayTagContainer& otherContainer) const
{
	SCOPE_CYCLE_COUNTER(STAT_FOrbGameplayTagContainer_Filter);

	FOrbGameplayTagContainer resultContainer;

	for (const TTuple<FGameplayTag, FOrbGameplayTagContainerEntry>& tag : otherContainer)
	{
		if (TagMatchesAny(tag.Key))
		{
			FOrbGameplayTagContainerEntry infoCopy = tag.Value;
			resultContainer.GameplayTags.Add(tag.Key, infoCopy);
		}
	}

	return resultContainer;
}

FGameplayTagContainer FOrbGameplayTagContainer::FilterExact(const FGameplayTagContainer& otherContainer) const
{
	SCOPE_CYCLE_COUNTER(STAT_FOrbGameplayTagContainer_Filter);

	FGameplayTagContainer resultContainer;

	for (const FGameplayTag& tag : otherContainer)
	{
		if (TagMatchesAnyExact(tag))
		{
			resultContainer.AddTagFast(tag);
		}
	}

	return resultContainer;
}

FGameplayTagContainer FOrbGameplayTagContainer::FilterExact(const FOrbGameplayTagContainer& otherContainer) const
{
	SCOPE_CYCLE_COUNTER(STAT_FOrbGameplayTagContainer_Filter);

	FGameplayTagContainer resultContainer;

	for (const TTuple<FGameplayTag, FOrbGameplayTagContainerEntry>& tag : otherContainer)
	{
		if (TagMatchesAnyExact(tag.Key))
		{
			resultContainer.AddTagFast(tag.Key);
		}
	}

	return resultContainer;
}

FOrbGameplayTagContainer FOrbGameplayTagContainer::FilterMultiExact(const FGameplayTagContainer& otherContainer) const
{
	SCOPE_CYCLE_COUNTER(STAT_FOrbGameplayTagContainer_Filter);

	FOrbGameplayTagContainer resultContainer;

	for (const TTuple<FGameplayTag, FOrbGameplayTagContainerEntry>& tag : GameplayTags)
	{
		if (tag.Key.MatchesAnyExact(otherContainer))
		{
			FOrbGameplayTagContainerEntry infoCopy = tag.Value;
			resultContainer.GameplayTags.Add(tag.Key, infoCopy);
		}
	}

	return resultContainer;
}

FOrbGameplayTagContainer FOrbGameplayTagContainer::FilterMultiExact(const FOrbGameplayTagContainer& otherContainer) const
{
	SCOPE_CYCLE_COUNTER(STAT_FOrbGameplayTagContainer_Filter);

	FOrbGameplayTagContainer resultContainer;

	for (const TTuple<FGameplayTag, FOrbGameplayTagContainerEntry>& tag : otherContainer)
	{
		if (TagMatchesAnyExact(tag.Key))
		{
			FOrbGameplayTagContainerEntry infoCopy = tag.Value;
			resultContainer.GameplayTags.Add(tag.Key, infoCopy);
		}
	}

	return resultContainer;
}

bool FOrbGameplayTagContainer::MatchesQuery(const FGameplayTagQuery& query) const
{
	FGameplayTagContainer container;
	GetContainerConst(container);
	return query.Matches(container);
}

void FOrbGameplayTagContainer::AppendTags(FGameplayTagContainer const& other)
{
	const int32 otherSize = other.Num();
	if(otherSize > 0)
	{
		const int32 thisSize = GameplayTags.Num();

		if(thisSize < otherSize)
		{
			GameplayTags.Reserve(GameplayTags.Num() + (otherSize - thisSize));
		}
	
		// Add other container's tags to our own
		for(const FGameplayTag& otherTag : other)
		{
			AddTag(otherTag);
		}
	}
}

void FOrbGameplayTagContainer::AppendTags(FOrbGameplayTagContainer const& other)
{
	const int32 thisSize = GameplayTags.Num();
	const int32 otherSize = other.Num();
	
	if(thisSize < otherSize)
	{
		GameplayTags.Reserve(GameplayTags.Num() + (otherSize - thisSize));
	}
	
	// Add other container's tags to our own
	for(const TTuple<FGameplayTag, FOrbGameplayTagContainerEntry>& otherTag : other)
	{
		if(otherTag.Value.ExplicitCount > 0)
		{
			AddTag(otherTag.Key, otherTag.Value.ExplicitCount);
		}
	}
}

void FOrbGameplayTagContainer::AppendMatchingTags(FGameplayTagContainer const& otherA, FGameplayTagContainer const& otherB)
{
	for(const FGameplayTag& otherATag : otherA)
	{
		if (otherATag.MatchesAny(otherB))
		{
			AddTag(otherATag);
		}
	}
}

void FOrbGameplayTagContainer::AppendMatchingTags(FOrbGameplayTagContainer const& otherA, FGameplayTagContainer const& otherB)
{
	for(const TTuple<FGameplayTag, FOrbGameplayTagContainerEntry>& otherATag : otherA)
	{
		if(otherATag.Value.ExplicitCount > 0)
		{
			if (otherATag.Key.MatchesAny(otherB))
			{
				AddTag(otherATag.Key, otherATag.Value.ExplicitCount);
			}
		}
	}
}

void FOrbGameplayTagContainer::AppendMatchingTags(FGameplayTagContainer const& otherA, FOrbGameplayTagContainer const& otherB)
{
	for(const FGameplayTag& otherATag : otherA)
	{
		if (otherB.TagMatchesAny(otherATag))
		{
			AddTag(otherATag);
		}
	}
}

void FOrbGameplayTagContainer::AppendMatchingTags(FOrbGameplayTagContainer const& otherA, FOrbGameplayTagContainer const& otherB)
{
	for(const TTuple<FGameplayTag, FOrbGameplayTagContainerEntry>& otherATag : otherA)
	{
		if(otherATag.Value.ExplicitCount > 0)
		{
			if (otherB.TagMatchesAny(otherATag.Key))
			{
				AddTag(otherATag.Key, otherATag.Value.ExplicitCount);
			}
		}
	}
}

void FOrbGameplayTagContainer::RemoveTags(const FGameplayTagContainer& tagsToRemove)
{
	for(const FGameplayTag& tag : tagsToRemove)
	{
		RemoveTag(tag);
	}
}

void FOrbGameplayTagContainer::RemoveTags(const FOrbGameplayTagContainer& tagsToRemove)
{
	for(const TTuple<FGameplayTag, FOrbGameplayTagContainerEntry>& tag : tagsToRemove)
	{
		if(tag.Value.ExplicitCount > 0)
		{
			RemoveTag(tag.Key, tag.Value.ExplicitCount);
		}
	}
}

void FOrbGameplayTagContainer::RemoveTag(const FGameplayTag& tagToRemove)
{
	RemoveTag(tagToRemove, 1);
}

void FOrbGameplayTagContainer::RemoveTag(const FGameplayTag& tagToRemove, int32 explicitCount)
{
	bool isExplicit = true;
	FGameplayTagContainer tagContainer = tagToRemove.GetGameplayTagParents();
	for(const FGameplayTag& tag : tagContainer)
	{
		explicitCount = RemoveTagFromMap(tag, explicitCount, isExplicit);
		if(isExplicit)
		{
			if(explicitCount <= 0)
				break;

			isExplicit = false;
		}
	}
}

int32 FOrbGameplayTagContainer::RemoveTagFromMap(const FGameplayTag& tagToRemove, int32 count, bool isExplicit)
{
	if(FOrbGameplayTagContainerEntry* entry = GameplayTags.Find(tagToRemove))
	{
		if(isExplicit && count > entry->ExplicitCount)
			count = entry->ExplicitCount;

		if(count > 0)
		{
			if(isExplicit)
				entry->ExplicitCount -= count;

			entry->Count -= count;

			if(!IsTagCountChangedEventPaused)
			{
				if(isExplicit)
					OnExactTagCountChangedDelegate.Broadcast(tagToRemove, entry->ExplicitCount);
				
				OnTagCountChangedDelegate.Broadcast(tagToRemove, entry->Count);
			}
		}

		if(entry->Count <= 0)
			GameplayTags.Remove(tagToRemove);
	}
	else count = 0;
		

	return count;
}

void FOrbGameplayTagContainer::AddTag(const FGameplayTag& tagToAdd)
{
	AddTag(tagToAdd, 1);
}

void FOrbGameplayTagContainer::AddTag(const FGameplayTag& tagToAdd, int32 explicitCount)
{
	//AddTagToMap(TagToAdd, explicitCount, true);
	bool isExplicit = true;
	FGameplayTagContainer tagContainer = tagToAdd.GetGameplayTagParents();
	for(const FGameplayTag& tag : tagContainer)
	{
		AddTagToMap(tag, explicitCount, isExplicit);
		isExplicit = false;
	}
}

void FOrbGameplayTagContainer::AddTagToMap(const FGameplayTag& tagToAdd, int32 count, bool isExplicit)
{
	FOrbGameplayTagContainerEntry* entry = GameplayTags.Find(tagToAdd);

	if(!entry)
	{
		entry = &GameplayTags.Add(tagToAdd, FOrbGameplayTagContainerEntry());
	}

	if(entry)
	{
		if(isExplicit)
			entry->ExplicitCount += count;

		entry->Count += count;

		if(!IsTagCountChangedEventPaused)
		{
			if(isExplicit)
				OnExactTagCountChangedDelegate.Broadcast(tagToAdd, entry->ExplicitCount);
			
			OnTagCountChangedDelegate.Broadcast(tagToAdd, entry->Count);
		}
			
	}
}

const FGameplayTagContainer& FOrbGameplayTagContainer::GetAsContainer()
{
	return GetContainer();
}

void FOrbGameplayTagContainer::PauseTagChangedEvent()
{
	IsTagCountChangedEventPaused = true;
}

void FOrbGameplayTagContainer::ContinuePauseTagChangedEvent()
{
	IsTagCountChangedEventPaused = false;
}

void FOrbGameplayTagContainer::SendTagCountStateAsChange()
{
	for(const TTuple<FGameplayTag, FOrbGameplayTagContainerEntry>& tag : GameplayTags)
	{
		OnExactTagCountChangedDelegate.Broadcast(tag.Key, tag.Value.ExplicitCount);
		OnTagCountChangedDelegate.Broadcast(tag.Key, tag.Value.Count);
	}
}

bool FOrbGameplayTagContainer::IsChangedEventPaused() const
{
	return IsTagCountChangedEventPaused;
}

void FOrbGameplayTagContainer::Reset()
{
	Empty();
	OnTagCountChangedDelegate.Clear();
	OnExactTagCountChangedDelegate.Clear();
	ContinuePauseTagChangedEvent();
}

void FOrbGameplayTagContainer::Empty()
{
	GameplayTags.Reset();
}

FString FOrbGameplayTagContainer::ToString() const
{
	FString exportString;
	FOrbGameplayTagContainer::StaticStruct()->ExportText(exportString, this, this, nullptr, 0, nullptr);

	return exportString;
}

void FOrbGameplayTagContainer::FromExportString(const FString& exportString, int32 portFlags)
{
	Reset();

	FOutputDeviceNull NullOut;
	FOrbGameplayTagContainer::StaticStruct()->ImportText(*exportString, this, nullptr, portFlags, &NullOut, TEXT("FOrbGameplayTagContainer"), true);
}

FString FOrbGameplayTagContainer::ToStringSimple(bool isQuoted) const
{
	FString retString;
	for (const TTuple<FGameplayTag, FOrbGameplayTagContainerEntry>& gameplayTag : GameplayTags)
	{
		if (isQuoted)
		{
			retString += TEXT("\"");
		}
		retString += gameplayTag.Key.ToString();
		if (isQuoted)
		{
			retString += TEXT("\"");
		}
		retString += TEXT(", ");
	}
	return retString;
}

TArray<FString> FOrbGameplayTagContainer::ToStringsMaxLen(int32 maxLen) const
{
	// caveat, if MaxLen < than a tag string, full string will be put in array (as a single line in the array)
	// since this is used for debug output.  If need to clamp, it can be added.  Also, strings will end in ", " to 
	// avoid extra complication.
	TArray<FString> retStrings;
	FString curLine;
	curLine.Reserve(maxLen);

	for (const auto & GameplayTag : GameplayTags)
	{
		FString TagString = GameplayTag.Key.ToString();
		TagString += TEXT(",");
		// Add 1 for space
		if (curLine.Len() + TagString.Len() + 1 >= maxLen)
		{
			retStrings.Add(curLine);
			curLine = TagString;
		} 
		else
		{
			curLine += TagString + TEXT(" ");
		}
	}
	if (curLine.Len() > 0)
	{
		retStrings.Add(curLine);
	}
	return retStrings;
}

FText FOrbGameplayTagContainer::ToMatchingText(EGameplayContainerMatchType matchType, bool bInvertCondition) const
{
	enum class EMatchingTypes : int8
	{
		Inverted	= 0x01,
		All			= 0x02
	};

#define LOCTEXT_NAMESPACE "FOrbGameplayTagContainer"
	const FText MatchingDescription[] =
	{
		LOCTEXT("MatchesAnyGameplayTags", "Has any tags in set: {GameplayTagSet}"),
		LOCTEXT("NotMatchesAnyGameplayTags", "Does not have any tags in set: {GameplayTagSet}"),
		LOCTEXT("MatchesAllGameplayTags", "Has all tags in set: {GameplayTagSet}"),
		LOCTEXT("NotMatchesAllGameplayTags", "Does not have all tags in set: {GameplayTagSet}")
	};
#undef LOCTEXT_NAMESPACE

	int32 DescriptionIndex = bInvertCondition ? static_cast<int32>(EMatchingTypes::Inverted) : 0;
	switch (matchType)
	{
	case EGameplayContainerMatchType::All:
		DescriptionIndex |= static_cast<int32>(EMatchingTypes::All);
		break;

	case EGameplayContainerMatchType::Any:
		break;

	default:
		UE_LOG(LogGameplayTags, Warning, TEXT("Invalid value for TagsToMatch (EGameplayContainerMatchType) %d.  Should only be Any or All."), static_cast<int32>(matchType));
		break;
	}

	FFormatNamedArguments Arguments;
	Arguments.Add(TEXT("GameplayTagSet"), FText::FromString(*ToString()));
	return FText::Format(MatchingDescription[DescriptionIndex], Arguments);
}

bool FOrbGameplayTagContainer::TagMatchesAny(const FGameplayTag& tagToCheck) const
{
	if (const FGameplayTagContainer* tagContainer = UGameplayTagsManager::Get().GetSingleTagContainer(tagToCheck))
	{
		return HasAny(*tagContainer);
	}

	// This should always be invalid if the node is missing
	ensureMsgf(!IsValid(), TEXT("Valid tag failed to conver to single tag container. %s"), *tagToCheck.ToString() );
	return false;
}

bool FOrbGameplayTagContainer::TagMatchesAnyExact(const FGameplayTag& tagToCheck) const
{
	if (const FGameplayTagContainer* tagContainer = UGameplayTagsManager::Get().GetSingleTagContainer(tagToCheck))
	{
		return HasAnyExact(*tagContainer);
	}

	// This should always be invalid if the node is missing
	ensureMsgf(!IsValid(), TEXT("Valid tag failed to conver to single tag container. %s"), *tagToCheck.ToString() );
	return false;
}

FGameplayTagContainer& FOrbGameplayTagContainer::GetContainer()
{
	if(!IsCachedTagContainerValid)
	{
		IsCachedTagContainerValid = true;
		GetThisContainerVersion(GameplayTagContainer);
	}

	return GameplayTagContainer;
}

void FOrbGameplayTagContainer::GetContainerConst(FGameplayTagContainer& container) const
{
	if(IsCachedTagContainerValid)
	{
		container = GameplayTagContainer;
	}
	else
	{
		GetThisContainerVersion(container);
	}
}

void FOrbGameplayTagContainer::GetThisContainerVersion(FGameplayTagContainer& container) const
{
	MakeContainer(container, true);
}

void FOrbGameplayTagContainer::MakeContainer(FGameplayTagContainer& container, bool exact) const
{
	TArray<FGameplayTag> gameplayTags;
	GetAsArray(gameplayTags, exact);
	container = FGameplayTagContainer::CreateFromArray(gameplayTags);
}
