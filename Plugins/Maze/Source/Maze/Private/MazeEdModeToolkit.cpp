// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "MazeEdModeToolkit.h"
#include "MazeEdMode.h"
#include "Engine/Selection.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Input/SComboButton.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Images/SImage.h"
#include "EditorStyleSet.h"
#include "TestUI.h" // testing if UI works with reflection
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "CoreMinimal.h"
#include "Editor/EditorEngine.h"
#include "Engine/GameEngine.h"
#include "EditorModeManager.h"

#define LOCTEXT_NAMESPACE "FMazeEdModeToolkit"

FMazeEdModeToolkit::FMazeEdModeToolkit()
{
}

FReply FMazeEdModeToolkit::OnClickedRoombasedMode()
{
	//BuildingMode = Roombased;
	UE_LOG(LogTemp, Warning, TEXT("Roombased mode."));

	InstantiateNewObject();

	return FReply::Handled();
}

FReply FMazeEdModeToolkit::OnClickedCavebasedMode()
{
	//BuildingMode = Cavebased;
	UE_LOG(LogTemp, Warning, TEXT("Cavebased mode."));

	InstantiateNewObject();

	return FReply::Handled();
}

FReply FMazeEdModeToolkit::InstantiateNewObject()
{
	MyArray.Init(10, 5);
	UWorld* EditorWorld = GEditor->GetEditorWorldContext().World();

	FActorSpawnParameters SpawnInfo;
	FVector Location = FVector(0.0f);
	FRotator Rotation = FRotator(0, 0, 0);

	test = (ATestUI*)EditorWorld->SpawnActor(ATestUI::StaticClass(), &Location, &Rotation);
	test->Init(1, 2, 3.5f, MyArray);

	UE_LOG(LogTemp, Warning, TEXT("New object."));

	return FReply::Handled();
}

/*TSharedRef<SWidget> FMazeEdModeToolkit::CreateBuildingModeButton()
{
	switch (BuildingMode)
	{
		case Roombased:
		{
			UE_LOG(LogTemp, Warning, TEXT("Roombased!!!"));

			return SAssignNew(BuildingModeButton, SButton)
				   .Text(FText::FromString("Create Roombased Maze"))
				   .OnClicked(this, &FMazeEdModeToolkit::InstantiateNewObject);
		}
		case Cavebased:
		{
			UE_LOG(LogTemp, Warning, TEXT("Cavebased!!!"));

			return SAssignNew(BuildingModeButton, SButton)
				   .Text(FText::FromString("Create Cavebased Maze"))
				   .OnClicked(this, &FMazeEdModeToolkit::InstantiateNewObject);
		}
		default:
		{
			UE_LOG(LogTemp, Warning, TEXT("Nothing specified!!!"));

			return SAssignNew(BuildingModeButton, SButton)
				   .Text(FText::FromString("No building mode specified."));
				   //.OnClicked(this, &FMazeEdModeToolkit::InstantiateNewObject);
		}

	}
}*/

void FMazeEdModeToolkit::Init(const TSharedPtr<IToolkitHost>& InitToolkitHost)
{
	struct Locals
	{
		static FReply OnButtonClick(FVector InOffset)
		{
			USelection* SelectedActors = GEditor->GetSelectedActors();

			// Let editor know that we're about to do something that we want to undo/redo
			GEditor->BeginTransaction(LOCTEXT("MoveActorsTransactionName", "MoveActors"));

			// For each selected actor
			for (FSelectionIterator Iter(*SelectedActors); Iter; ++Iter)
			{
				if (AActor* LevelActor = Cast<AActor>(*Iter))
				{
					// Register actor in opened transaction (undo/redo)
					LevelActor->Modify();
					// Move actor to given location
					LevelActor->TeleportTo(LevelActor->GetActorLocation() + InOffset, FRotator(0, 0, 0));
				}
			}

			// We're done moving actors so close transaction
			GEditor->EndTransaction();

			return FReply::Handled();
		}
			   
	};

	const float Factor = 256.0f;

	SAssignNew(ToolkitWidget, SBorder)
		.HAlign(HAlign_Center)
		.Padding(25)
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			.AutoHeight()
			.HAlign(HAlign_Center)
			.Padding(50)
			[
				SNew(STextBlock)
				.AutoWrapText(true)
				.Text(LOCTEXT("HelperLabel", "Choose maze mode:"))
			]

			//--------------------------------------------------------------------------------------
			/*
			+ SVerticalBox::Slot()
				.AutoHeight()
				[
					SNew(SComboButton)
					.ContentPadding(0)
				    .ButtonContent()
				    [
						SNew(STextBlock)
						.Text(FText::FromString("Choose maze mode:"))
				    ]
					.MenuContent()
					[
						SNew(SVerticalBox)

						+ SVerticalBox::Slot()
						.AutoHeight()
						.HAlign(HAlign_Center)
						.Padding(0)
						[
							SNew(SButton)
							.ButtonColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f, 0.0f))
							.Text(FText::FromString("Roombased"))
							.ForegroundColor(FLinearColor(255.0f, 255.0f, 255.0f, 1.0f))
							.OnClicked(this, &FMazeEdModeToolkit::OnClickedRoombasedMode)
						]

						+ SVerticalBox::Slot()
						.AutoHeight()
						.HAlign(HAlign_Center)
						.Padding(0)
						[
							SNew(SButton)
							.ButtonColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f, 0.0f))
							.Text(FText::FromString("Cavebased"))
							.ForegroundColor(FLinearColor(255.0f, 255.0f, 255.0f, 1.0f))
							.OnClicked(this, &FMazeEdModeToolkit::OnClickedCavebasedMode)
						]
					]
				]

				*/

			+ SVerticalBox::Slot()
				.AutoHeight()
				.HAlign(HAlign_Center)
				.Padding(10)
				[
					SNew(SButton)
					.Text(FText::FromString("Create Roombased Maze"))
				.OnClicked(this, &FMazeEdModeToolkit::OnClickedRoombasedMode)
				]

			+ SVerticalBox::Slot()
				.AutoHeight()
				.HAlign(HAlign_Center)
				.Padding(10)
				[
					SNew(SButton)
					.Text(FText::FromString("Create Cavebased Maze"))
					.OnClicked(this, &FMazeEdModeToolkit::OnClickedCavebasedMode)
				]		

			+ SVerticalBox::Slot()
				.AutoHeight()
				.HAlign(HAlign_Center)
				.Padding(10)
				[
					SNew(SButton)
					.Text(FText::FromString("Spawn an AI enemy."))
				    .OnClicked(this, &FMazeEdModeToolkit::InstantiateNewObject)
				]

		];
		
	FModeToolkit::Init(InitToolkitHost);
}

FName FMazeEdModeToolkit::GetToolkitFName() const
{
	return FName("MazeEdMode");
}

FText FMazeEdModeToolkit::GetBaseToolkitName() const
{
	return NSLOCTEXT("MazeEdModeToolkit", "DisplayName", "MazeEdMode Tool");
}

class FEdMode* FMazeEdModeToolkit::GetEditorMode() const
{
	return GLevelEditorModeTools().GetActiveMode(FMazeEdMode::EM_MazeEdModeId);
}

#undef LOCTEXT_NAMESPACE
