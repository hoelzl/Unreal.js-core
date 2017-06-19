#include "JavascriptGraphEdNode.h"
#include "JavascriptGraphAssetGraphSchema.h"

#define LOCTEXT_NAMESPACE "JavascriptGraphEdNode"

void UJavascriptGraphEdNode::AllocateDefaultPins()
{
	auto Schema = CastChecked<UJavascriptGraphAssetGraphSchema>(GetSchema());
	Schema->OnAllocateDefaultPins.ExecuteIfBound(this);
}

void UJavascriptGraphEdNode::NodeConnectionListChanged()
{
	Super::NodeConnectionListChanged();

	auto Schema = CastChecked<UJavascriptGraphAssetGraphSchema>(GetSchema());
	Schema->OnNodeConnectionListChanged.ExecuteIfBound(this);
}

void UJavascriptGraphEdNode::PinConnectionListChanged(UEdGraphPin* Pin)
{
	Super::PinConnectionListChanged(Pin);

	auto Schema = CastChecked<UJavascriptGraphAssetGraphSchema>(GetSchema());
	Schema->OnPinConnectionListChanged.ExecuteIfBound(FJavascriptEdGraphPin{ const_cast<UEdGraphPin*>(Pin) });
}

UJavascriptGraphEdGraph* UJavascriptGraphEdNode::GetGenericGraphEdGraph()
{
	return Cast<UJavascriptGraphEdGraph>(GetGraph());
}

FText UJavascriptGraphEdNode::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	if (GraphNode)
	{
		auto Schema = CastChecked<UJavascriptGraphAssetGraphSchema>(GetSchema());
		if (Schema->OnGetString.IsBound())
		{
			return Schema->OnGetString.Execute(this, EGraphSchemaGetStringQuery::Title);
		}
	}

	return FText();
}

FText UJavascriptGraphEdNode::GetDescription() const
{
	auto Schema = CastChecked<UJavascriptGraphAssetGraphSchema>(GetSchema());
	if (Schema->OnGetString.IsBound())
	{
		return Schema->OnGetString.Execute(this,EGraphSchemaGetStringQuery::Description);
	}
	
	return FText();
}

#if 1
FJavascriptEdGraphPin UJavascriptGraphEdNode::CreatePin(
	EEdGraphPinDirection Dir,
	const FString& PinCategory,
	const FString& PinSubCategory,
	UObject* PinSubCategoryObject,
	bool bIsArray,
	bool bIsReference,
	const FString& PinName,
	bool bIsConst /*= false*/
				  //int32 Index /*= INDEX_NONE*/
	)
{
	return FJavascriptEdGraphPin{
#ifdef UE_4_17_OR_LATER
		EPinContainerType ContainerType = bIsArray ? EPinContainerType::Array : EPinContainerType::None;
	    Super::CreatePin(Dir, PinCategory, PinSubCategory, PinSubCategoryObject, PinName, ContainerType, bIsReference, bIsConst, INDEX_NONE)
#else
		Super::CreatePin(Dir, PinCategory, PinSubCategory, PinSubCategoryObject, bIsArray, bIsReference, PinName, bIsConst, INDEX_NONE)
#endif
	};
}

#else
FJavascriptEdGraphPin UJavascriptGraphEdNode::CreatePin(
	EEdGraphPinDirection Dir, 
	const FString& PinCategory, 
	const FString& PinSubCategory, 
	UObject* PinSubCategoryObject, 
	const FString& PinName, 
	EPinContainerType PinContainerType, 
	bool bIsReference,
	bool bIsConst
	/*int32 Index /*= INDEX_NONE*/
    )
{
	return FJavascriptEdGraphPin{
		Super::CreatePin(Dir, PinCategory, PinSubCategory, PinSubCategoryObject, PinName, PinContainerType, bIsReference, bIsConst, INDEX_NONE)
	};
}
#endif

#undef LOCTEXT_NAMESPACE
