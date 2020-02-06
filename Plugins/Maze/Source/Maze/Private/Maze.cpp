// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "Maze.h"
#include "MazeEdMode.h"

#define LOCTEXT_NAMESPACE "FMazeModule"

DEFINE_LOG_CATEGORY(Maze);

void FMazeModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	FEditorModeRegistry::Get().RegisterMode<FMazeEdMode>(FMazeEdMode::EM_MazeEdModeId, LOCTEXT("MazeEdModeName", "MazeEdMode"), FSlateIcon(), true);
}

void FMazeModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	FEditorModeRegistry::Get().UnregisterMode(FMazeEdMode::EM_MazeEdModeId);
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FMazeModule, Maze)