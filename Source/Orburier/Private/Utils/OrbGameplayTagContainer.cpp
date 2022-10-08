// Fill out your copyright notice in the Description page of Project Settings.


#include "Utils/OrbGameplayTagContainer.h"
#include "GameplayTagsManager.h"
#include "Misc/OutputDeviceNull.h"


DECLARE_CYCLE_STAT(TEXT("FOrbGameplayTagContainer::Filter"), STAT_FOrbGameplayTagContainer_Filter, STATGROUP_GameplayTags);

FOrbGameplayTagContainer& FOrbGameplayTagContainer::operator=(FOrbGameplayTagContainer const& Other)
{
	// Guard against self-assignment
	if (this == &Other)
	{
		return *this;
	}
	GameplayTags.Empty(Other.GameplayTags.Num());
	GameplayTags.Append(Other.GameplayTags);

	return *this;
}

FOrbGameplayTagContainer& FOrbGameplayTagContainer::operator=(FOrbGameplayTagContainer&& Other) noexcept
{
	GameplayTags = MoveTemp(Other.GameplayTags);
	return *this;
}

bool FOrbGameplayTagContainer::operator==(FOrbGameplayTagContainer const& Other) const
{
	// This is to handle the case where the two containers are in different orders
	if (GameplayTags.Num() != Other.GameplayTags.Num())
	{
		return false;
	}

	for (const TTuple<FGameplayTag, FOrbGameplayTagContainerEntry>& Tag : Other.GameplayTags)
	{
		if(const FOrbGameplayTagContainerEntry* ThisTagEntry = GameplayTags.Find(Tag.Key); !ThisTagEntry || ThisTagEntry->Count != Tag.Value.Count)
			return false;
	}

	return true;
}

bool FOrbGameplayTagContainer::operator!=(FOrbGameplayTagContainer const& Other) const
{
	return !operator==(Other);
}

//FGameplayTagContainer FOrbGameplayTagContainer::Filter(const FGameplayTagContainer& otherContainer) const
//{
//	SCOPE_CYCLE_COUNTER(STAT_FOrbGameplayTagContainer_Filter);
//
//	FGameplayTagContainer resultContainer;
//
//	for (const TTuple<FGameplayTag, FOrbGameplayTagContainerEntry>& tag : GameplayTags)
//	{
//		if (tag.Key.MatchesAny(otherContainer))
//		{
//			resultContainer.AddTagFast(tag.Key);
//		}
//	}
//
//	return resultContainer;
//}
//
//FGameplayTagContainer FOrbGameplayTagContainer::Filter(const FOrbGameplayTagContainer& otherContainer) const
//{
//	SCOPE_CYCLE_COUNTER(STAT_FOrbGameplayTagContainer_Filter);
//
//	FGameplayTagContainer resultContainer;
//
//	for (const TTuple<FGameplayTag, FOrbGameplayTagContainerEntry>& tag : otherContainer.GameplayTags)
//	{
//		if (TagMatchesAny(tag.Key))
//		{
//			resultContainer.AddTagFast(tag.Key);
//		}
//	}
//
//	return resultContainer;
//}
//
//FOrbGameplayTagContainer FOrbGameplayTagContainer::FilterMulti(const FGameplayTagContainer& otherContainer) const
//{
//	SCOPE_CYCLE_COUNTER(STAT_FOrbGameplayTagContainer_Filter);
//
//	FOrbGameplayTagContainer resultContainer;
//
//	for (const TTuple<FGameplayTag, FOrbGameplayTagContainerEntry>& tag : GameplayTags)
//	{
//		if (tag.Key.MatchesAny(otherContainer))
//		{
//			FOrbGameplayTagContainerEntry infoCopy = tag.Value;
//			resultContainer.GameplayTags.Add(tag.Key, infoCopy);
//		}
//	}
//
//	return resultContainer;
//}
//
//FOrbGameplayTagContainer FOrbGameplayTagContainer::FilterMulti(const FOrbGameplayTagContainer& otherContainer) const
//{
//	SCOPE_CYCLE_COUNTER(STAT_FOrbGameplayTagContainer_Filter);
//
//	FOrbGameplayTagContainer resultContainer;
//
//	for (const TTuple<FGameplayTag, FOrbGameplayTagContainerEntry>& tag : otherContainer.GameplayTags)
//	{
//		if (TagMatchesAny(tag.Key))
//		{
//			FOrbGameplayTagContainerEntry infoCopy = tag.Value;
//			resultContainer.GameplayTags.Add(tag.Key, infoCopy);
//		}
//	}
//
//	return resultContainer;
//}
//
//FGameplayTagContainer FOrbGameplayTagContainer::FilterExact(const FGameplayTagContainer& otherContainer) const
//{
//	SCOPE_CYCLE_COUNTER(STAT_FOrbGameplayTagContainer_Filter);
//
//	FGameplayTagContainer resultContainer;
//
//	for (const FGameplayTag& tag : otherContainer)
//	{
//		if (TagMatchesAnyExact(tag))
//		{
//			resultContainer.AddTagFast(tag);
//		}
//	}
//
//	return resultContainer;
//}
//
//FGameplayTagContainer FOrbGameplayTagContainer::FilterExact(const FOrbGameplayTagContainer& otherContainer) const
//{
//	SCOPE_CYCLE_COUNTER(STAT_FOrbGameplayTagContainer_Filter);
//
//	FGameplayTagContainer resultContainer;
//
//	for (const TTuple<FGameplayTag, FOrbGameplayTagContainerEntry>& tag : otherContainer.GameplayTags)
//	{
//		if (TagMatchesAnyExact(tag.Key))
//		{
//			resultContainer.AddTagFast(tag.Key);
//		}
//	}
//
//	return resultContainer;
//}
//
//FOrbGameplayTagContainer FOrbGameplayTagContainer::FilterMultiExact(const FGameplayTagContainer& otherContainer) const
//{
//	SCOPE_CYCLE_COUNTER(STAT_FOrbGameplayTagContainer_Filter);
//
//	FOrbGameplayTagContainer resultContainer;
//
//	for (const TTuple<FGameplayTag, FOrbGameplayTagContainerEntry>& tag : GameplayTags)
//	{
//		if (tag.Key.MatchesAnyExact(otherContainer))
//		{
//			FOrbGameplayTagContainerEntry infoCopy = tag.Value;
//			resultContainer.GameplayTags.Add(tag.Key, infoCopy);
//		}
//	}
//
//	return resultContainer;
//}
//
//FOrbGameplayTagContainer FOrbGameplayTagContainer::FilterMultiExact(const FOrbGameplayTagContainer& otherContainer) const
//{
//	SCOPE_CYCLE_COUNTER(STAT_FOrbGameplayTagContainer_Filter);
//
//	FOrbGameplayTagContainer resultContainer;
//
//	for (const TTuple<FGameplayTag, FOrbGameplayTagContainerEntry>& tag : otherContainer.GameplayTags)
//	{
//		if (TagMatchesAnyExact(tag.Key))
//		{
//			FOrbGameplayTagContainerEntry infoCopy = tag.Value;
//			resultContainer.GameplayTags.Add(tag.Key, infoCopy);
//		}
//	}
//
//	return resultContainer;
//}

void FOrbGameplayTagContainer::AppendTags(FGameplayTagContainer const& Other)
{
	if(const int32 OtherSize = Other.Num(); OtherSize > 0)
	{
		if(const int32 ThisSize = GameplayTags.Num(); ThisSize < OtherSize)
		{
			GameplayTags.Reserve(GameplayTags.Num() + (OtherSize - ThisSize));
		}
	
		// Add other container's tags to our own
		for(const FGameplayTag& otherTag : Other)
		{
			AddTag(otherTag);
		}
	}
}

void FOrbGameplayTagContainer::AppendTags(FOrbGameplayTagContainer const& Other)
{
	const int32 ThisSize = GameplayTags.Num();

	if(const int32 OtherSize = Other.Num(); ThisSize < OtherSize)
	{
		GameplayTags.Reserve(GameplayTags.Num() + (OtherSize - ThisSize));
	}
	
	// Add other container's tags to our own
	for(const TTuple<FGameplayTag, FOrbGameplayTagContainerEntry>& OtherTag : Other.GameplayTags)
	{
		if(OtherTag.Value.ExplicitCount > 0)
		{
			AddTag(OtherTag.Key, OtherTag.Value.ExplicitCount);
		}
	}
}

//void FOrbGameplayTagContainer::AppendMatchingTags(FGameplayTagContainer const& otherA, FGameplayTagContainer const& otherB)
//{
//	for(const FGameplayTag& otherATag : otherA)
//	{
//		if (otherATag.MatchesAny(otherB))
//		{
//			AddTag(otherATag);
//		}
//	}
//}
//
//void FOrbGameplayTagContainer::AppendMatchingTags(FOrbGameplayTagContainer const& otherA, FGameplayTagContainer const& otherB)
//{
//	for(const TTuple<FGameplayTag, FOrbGameplayTagContainerEntry>& otherATag : otherA.GameplayTags)
//	{
//		if(otherATag.Value.ExplicitCount > 0)
//		{
//			if (otherATag.Key.MatchesAny(otherB))
//			{
//				AddTag(otherATag.Key, otherATag.Value.ExplicitCount);
//			}
//		}
//	}
//}
//
//void FOrbGameplayTagContainer::AppendMatchingTags(FGameplayTagContainer const& otherA, FOrbGameplayTagContainer const& otherB)
//{
//	for(const FGameplayTag& otherATag : otherA)
//	{
//		if (otherB.TagMatchesAny(otherATag))
//		{
//			AddTag(otherATag);
//		}
//	}
//}
//
//void FOrbGameplayTagContainer::AppendMatchingTags(FOrbGameplayTagContainer const& otherA, FOrbGameplayTagContainer const& otherB)
//{
//	for(const TTuple<FGameplayTag, FOrbGameplayTagContainerEntry>& otherATag : otherA.GameplayTags)
//	{
//		if(otherATag.Value.ExplicitCount > 0)
//		{
//			if (otherB.TagMatchesAny(otherATag.Key))
//			{
//				AddTag(otherATag.Key, otherATag.Value.ExplicitCount);
//			}
//		}
//	}
//}

void FOrbGameplayTagContainer::RemoveTags(const FGameplayTagContainer& TagsToRemove)
{
	for(const FGameplayTag& Tag : TagsToRemove)
	{
		RemoveTag(Tag);
	}
}

auto FOrbGameplayTagContainer::RemoveTags(const FOrbGameplayTagContainer& TagsToRemove) -> void
{
	for(const TTuple<FGameplayTag, FOrbGameplayTagContainerEntry>& Tag : TagsToRemove.GameplayTags)
	{
		if(Tag.Value.ExplicitCount > 0)
		{
			RemoveTag(Tag.Key, Tag.Value.ExplicitCount);
		}
	}
}

void FOrbGameplayTagContainer::RemoveTag(const FGameplayTag& TagToRemove)
{
	RemoveTag(TagToRemove, 1);
}

void FOrbGameplayTagContainer::RemoveTag(const FGameplayTag& TagToRemove, int32 ExplicitCount)
{
	bool IsExplicit = true;
	FGameplayTagContainer TagContainer = TagToRemove.GetGameplayTagParents();
	for(const FGameplayTag& Tag : TagContainer)
	{
		ExplicitCount = RemoveTagFromMap(Tag, ExplicitCount, IsExplicit);
		if(IsExplicit)
		{
			if(ExplicitCount <= 0)
				break;

			IsExplicit = false;
		}
	}
}

int32 FOrbGameplayTagContainer::RemoveTagFromMap(const FGameplayTag& TagToRemove, int32 Count, const bool IsExplicit)
{
	if(FOrbGameplayTagContainerEntry* Entry = GameplayTags.Find(TagToRemove))
	{
		if(IsExplicit && Count > Entry->ExplicitCount)
			Count = Entry->ExplicitCount;

		if(Count > 0)
		{
			if(IsExplicit)
			{
				Entry->ExplicitCount -= Count;

				if(Entry->ExplicitCount <= 0)
					ExplicitTagTypeCounter--;
			}
			
			Entry->Count -= Count;

			if(!IsTagCountChangedEventPaused)
			{
				if(IsExplicit)
					OnExactTagCountChangedDelegate.Broadcast(TagToRemove, Entry->ExplicitCount);
				
				OnTagCountChangedDelegate.Broadcast(TagToRemove, Entry->Count);
			}
		}

		if(Entry->Count <= 0)
		{
			if(IsTagCountChangedEventPaused) IsGameplayTagsMapDirty = true;
			else GameplayTags.Remove(TagToRemove);
		}
			
	}
	else Count = 0;
		

	return Count;
}

void FOrbGameplayTagContainer::AddTag(const FGameplayTag& TagToAdd)
{
	AddTag(TagToAdd, 1);
}

void FOrbGameplayTagContainer::AddTag(const FGameplayTag& TagToAdd, const int32 ExplicitCount)
{
	//AddTagToMap(TagToAdd, explicitCount, true);
	bool bIsExplicit = true;
	FGameplayTagContainer TagContainer = TagToAdd.GetGameplayTagParents();
	for(const FGameplayTag& Tag : TagContainer)
	{
		AddTagToMap(Tag, ExplicitCount, bIsExplicit);
		bIsExplicit = false;
	}
}

void FOrbGameplayTagContainer::AddTagToMap(const FGameplayTag& TagToAdd, const int32 Count, const bool IsExplicit)
{
	FOrbGameplayTagContainerEntry* Entry = GameplayTags.Find(TagToAdd);

	if(!Entry)
	{
		Entry = &GameplayTags.Add(TagToAdd, FOrbGameplayTagContainerEntry());
	}

	if(Entry && Count > 0)
	{
		if(IsExplicit)
		{
			if(Entry->ExplicitCount == 0)
				ExplicitTagTypeCounter++;
			
			Entry->ExplicitCount += Count;
		}

		Entry->Count += Count;

		if(!IsTagCountChangedEventPaused)
		{
			if(IsExplicit)
				OnExactTagCountChangedDelegate.Broadcast(TagToAdd, Entry->ExplicitCount);
			
			OnTagCountChangedDelegate.Broadcast(TagToAdd, Entry->Count);
		}
			
	}
}

void FOrbGameplayTagContainer::PauseTagChangedEvent()
{
	IsTagCountChangedEventPaused = true;
}

void FOrbGameplayTagContainer::ContinuePauseTagChangedEvent()
{
	IsTagCountChangedEventPaused = false;
	Compress();
}

void FOrbGameplayTagContainer::SendTagCountStateAsChange()
{
	const bool isPaused = IsChangedEventPaused();
	for(const TTuple<FGameplayTag, FOrbGameplayTagContainerEntry>& Tag : GameplayTags)
	{
		if(isPaused || Tag.Value.ExplicitCount > 0)
			OnExactTagCountChangedDelegate.Broadcast(Tag.Key, Tag.Value.ExplicitCount);
		
		OnTagCountChangedDelegate.Broadcast(Tag.Key, Tag.Value.Count);
	}
}

bool FOrbGameplayTagContainer::IsChangedEventPaused() const
{
	return IsTagCountChangedEventPaused;
}

void FOrbGameplayTagContainer::Compress()
{
	if(IsGameplayTagsMapDirty)
	{
		for(auto ItRemove = GameplayTags.CreateIterator(); ItRemove; ++ItRemove)
		{
			if(ItRemove.Value().Count <= 0)
				ItRemove.RemoveCurrent();
		}
		IsGameplayTagsMapDirty = false;
	}
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
	FString ExportString;
	FOrbGameplayTagContainer::StaticStruct()->ExportText(ExportString, this, this, nullptr, 0, nullptr);

	return ExportString;
}

auto FOrbGameplayTagContainer::FromExportString(const FString& ExportString, const int32 PortFlags) -> void
{
	Reset();

	FOutputDeviceNull NullOut;
	FOrbGameplayTagContainer::StaticStruct()->ImportText(*ExportString, this, nullptr, PortFlags, &NullOut, TEXT("FOrbGameplayTagContainer"), true);
}

FString FOrbGameplayTagContainer::ToStringSimple(const bool IsQuoted) const
{
	FString RetString;
	for (const TTuple<FGameplayTag, FOrbGameplayTagContainerEntry>& gameplayTag : GameplayTags)
	{
		if (IsQuoted)
		{
			RetString += TEXT("\"");
		}
		RetString += gameplayTag.Key.ToString();
		if (IsQuoted)
		{
			RetString += TEXT("\"");
		}
		RetString += TEXT(", ");
	}
	return RetString;
}

TArray<FString> FOrbGameplayTagContainer::ToStringsMaxLen(const int32 MaxLen) const
{
	// caveat, if MaxLen < than a tag string, full string will be put in array (as a single line in the array)
	// since this is used for debug output.  If need to clamp, it can be added.  Also, strings will end in ", " to 
	// avoid extra complication.
	TArray<FString> RetStrings;
	FString CurLine;
	CurLine.Reserve(MaxLen);

	for (const auto & GameplayTag : GameplayTags)
	{
		FString TagString = GameplayTag.Key.ToString();
		TagString += TEXT(",");
		// Add 1 for space
		if (CurLine.Len() + TagString.Len() + 1 >= MaxLen)
		{
			RetStrings.Add(CurLine);
			CurLine = TagString;
		} 
		else
		{
			CurLine += TagString + TEXT(" ");
		}
	}
	if (CurLine.Len() > 0)
	{
		RetStrings.Add(CurLine);
	}
	return RetStrings;
}

FText FOrbGameplayTagContainer::ToMatchingText(EGameplayContainerMatchType MatchType, const bool bInvertCondition) const
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
	switch (MatchType)
	{
	case EGameplayContainerMatchType::All:
		DescriptionIndex |= static_cast<int32>(EMatchingTypes::All);
		break;

	case EGameplayContainerMatchType::Any:
		break;

	default:
		UE_LOG(LogGameplayTags, Warning, TEXT("Invalid value for TagsToMatch (EGameplayContainerMatchType) %d.  Should only be Any or All."), static_cast<int32>(MatchType));
		break;
	}

	FFormatNamedArguments Arguments;
	Arguments.Add(TEXT("GameplayTagSet"), FText::FromString(*ToString()));
	return FText::Format(MatchingDescription[DescriptionIndex], Arguments);
}

bool FOrbGameplayTagContainer::TagMatchesAny(const FGameplayTag& TagToCheck) const
{
	if (const FGameplayTagContainer* TagContainer = UGameplayTagsManager::Get().GetSingleTagContainer(TagToCheck))
	{
		return HasAny(*TagContainer);
	}

	// This should always be invalid if the node is missing
	ensureMsgf(!IsValid(), TEXT("Valid tag failed to conver to single tag container. %s"), *TagToCheck.ToString() );
	return false;
}

bool FOrbGameplayTagContainer::TagMatchesAnyExact(const FGameplayTag& TagToCheck) const
{
	if (const FGameplayTagContainer* TagContainer = UGameplayTagsManager::Get().GetSingleTagContainer(TagToCheck))
	{
		return HasAnyExact(*TagContainer);
	}

	// This should always be invalid if the node is missing
	ensureMsgf(!IsValid(), TEXT("Valid tag failed to conver to single tag container. %s"), *TagToCheck.ToString() );
	return false;
}
