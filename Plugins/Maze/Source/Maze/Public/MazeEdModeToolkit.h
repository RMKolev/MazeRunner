// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BlockBuilderWrapper.h"
#include "BlockBuilder.h"
#include "Toolkits/BaseToolkit.h"

class FMazeEdModeToolkit : public FModeToolkit
{
public:

	FMazeEdModeToolkit();

	FReply OnClickedRoombasedWrapper();
	FReply OnClickedCavebasedWrapper();

	FReply OnClickedRoombasedMaze();
	FReply OnClickedCavebasedMaze();

	FReply InstantiateNewObject();
	
	/** FModeToolkit interface */
	virtual void Init(const TSharedPtr<IToolkitHost>& InitToolkitHost) override;

	/** IToolkit interface */
	virtual FName GetToolkitFName() const override;
	virtual FText GetBaseToolkitName() const override;
	virtual class FEdMode* GetEditorMode() const override;
	virtual TSharedPtr<class SWidget> GetInlineContent() const override { return ToolkitWidget; }

private:

	TSharedPtr<SWidget> ToolkitWidget;
	//TArray<int32> MyArray;
	//ATestUI* test;

	ABlockBuilderWrapper* CavebasedMazeWrapper;
};

