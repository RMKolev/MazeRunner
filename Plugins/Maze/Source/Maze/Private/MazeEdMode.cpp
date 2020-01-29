// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "MazeEdMode.h"
#include "MazeEdModeToolkit.h"
#include "Toolkits/ToolkitManager.h"
#include "EditorModeManager.h"

const FEditorModeID FMazeEdMode::EM_MazeEdModeId = TEXT("EM_MazeEdMode");

FMazeEdMode::FMazeEdMode()
{

}

FMazeEdMode::~FMazeEdMode()
{

}

void FMazeEdMode::Enter()
{
	FEdMode::Enter();

	if (!Toolkit.IsValid() && UsesToolkits())
	{
		Toolkit = MakeShareable(new FMazeEdModeToolkit);
		Toolkit->Init(Owner->GetToolkitHost());
	}
}

void FMazeEdMode::Exit()
{
	if (Toolkit.IsValid())
	{
		FToolkitManager::Get().CloseToolkit(Toolkit.ToSharedRef());
		Toolkit.Reset();
	}

	// Call base Exit method to ensure proper cleanup
	FEdMode::Exit();
}

bool FMazeEdMode::UsesToolkits() const
{
	return true;
}




