// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "TestUI.h"
#include "Toolkits/BaseToolkit.h"

/*
UENUM()
enum MazeBuildingMode
{
	Roombased    UMETA(DisplayName = "Roombased"),
	Cavebased    UMETA(DisplayName = "Cavebased")
	// it can be extended
};
*/

class FMazeEdModeToolkit : public FModeToolkit
{
public:

	FMazeEdModeToolkit();

	FReply OnClickedRoombasedMode();
	FReply OnClickedCavebasedMode();
	FReply InstantiateNewObject();
	//TSharedRef<SWidget> CreateBuildingModeButton();
	
	/** FModeToolkit interface */
	virtual void Init(const TSharedPtr<IToolkitHost>& InitToolkitHost) override;

	/** IToolkit interface */
	virtual FName GetToolkitFName() const override;
	virtual FText GetBaseToolkitName() const override;
	virtual class FEdMode* GetEditorMode() const override;
	virtual TSharedPtr<class SWidget> GetInlineContent() const override { return ToolkitWidget; }

private:

	TSharedPtr<SWidget> ToolkitWidget;
	//TSharedPtr<SWidget> BuildingModeButton;

	TArray<int32> MyArray;
	ATestUI* test;

	//MazeBuildingMode BuildingMode;
};