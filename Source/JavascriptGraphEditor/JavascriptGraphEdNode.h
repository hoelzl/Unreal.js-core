#pragma once

#include "JavascriptGraphEdGraph.h"
#include "JavascriptGraphEditorLibrary.h"
#include "EdGraph/EdGraphNode.h"
#include "JavascriptGraphEdNode.generated.h"

UCLASS(MinimalAPI)
class UJavascriptGraphEdNode : public UEdGraphNode
{
	GENERATED_BODY()

public:
	UPROPERTY()
	FSlateColor BackgroundColor;

	UPROPERTY(VisibleAnywhere, instanced, Category = "JavascriptGraph")
	UObject* GraphNode;
	
public:
	virtual void AllocateDefaultPins() override;
	virtual void NodeConnectionListChanged() override;
	virtual void PinConnectionListChanged(UEdGraphPin* Pin) override;

	UJavascriptGraphEdGraph* GetGenericGraphEdGraph();

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const;

	virtual FText GetDescription() const;	

#if 1
	UFUNCTION(BlueprintCallable, Category = "Scripting | Javascript")
	FJavascriptEdGraphPin CreatePin(
		EEdGraphPinDirection Dir,
		const FString& PinCategory,
		const FString& PinSubCategory,
		UObject* PinSubCategoryObject,
		bool bIsArray,
		bool bIsReference,
		const FString& PinName,
		bool bIsConst /*= false*/
		//int32 Index /*= INDEX_NONE*/
		);
#else
	UFUNCTION(BlueprintCallable, Category = "Scripting | Javascript")
	FJavascriptEdGraphPin CreatePin(
		EEdGraphPinDirection Dir,
		const FString& PinCategory,
		const FString& PinSubCategory,
		UObject* PinSubCategoryObject,
		const FString& PinName,
		EPinContainerType PinContainerType,
		bool bIsReference,
		bool bIsConst
		//int32 Index /*= INDEX_NONE*/
		);
#endif

public:
	UPROPERTY()
	bool Bidirectional;

	UPROPERTY()
	int32 PriorityOrder;
};
