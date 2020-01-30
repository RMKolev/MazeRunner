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

void FMazeEdModeToolkit::Init(const TSharedPtr<IToolkitHost>& InitToolkitHost)
{
	MyArray.Init(10, 5);
	UWorld * EditorWorld = GEditor->GetEditorWorldContext().World();
	test = (ATestUI*) EditorWorld->SpawnActor(ATestUI::StaticClass());
	test->Init(1, 2, 3.5f, MyArray);

	struct Locals
	{
		static bool IsWidgetEnabled()
		{
			return GEditor->GetSelectedActors()->Num() != 0;
		}

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

		static TSharedRef<SWidget> MakeButton(FText InLabel, const FVector InOffset)
		{
			return SNew(SButton)
				.Text(InLabel)
				.OnClicked_Static(&Locals::OnButtonClick, InOffset);
		}

	};

	const float Factor = 256.0f;

	SAssignNew(ToolkitWidget, SBorder)
		.HAlign(HAlign_Center)
		.Padding(25)
		//.IsEnabled_Static(&Locals::IsWidgetEnabled)
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			.AutoHeight()
			.HAlign(HAlign_Center)
			.Padding(50)
			[
				SNew(STextBlock)
				.AutoWrapText(true)
				.Text(LOCTEXT("HelperLabel", "Select some actors and move them around using buttons below"))
			]
			+ SVerticalBox::Slot()
				.HAlign(HAlign_Center)
				.AutoHeight()
				[
					Locals::MakeButton(LOCTEXT("UpButtonLabel", "Up"), FVector(0, 0, Factor))
				]
			+ SVerticalBox::Slot()
				.HAlign(HAlign_Center)
				.AutoHeight()
				[
					SNew(SHorizontalBox)
					+ SHorizontalBox::Slot()
					.AutoWidth()
					[
						Locals::MakeButton(LOCTEXT("LeftButtonLabel", "Left"), FVector(0, -Factor, 0))
					]
					+ SHorizontalBox::Slot()
						.AutoWidth()
						[
							Locals::MakeButton(LOCTEXT("RightButtonLabel", "Right"), FVector(0, Factor, 0))
						]
				]
			+ SVerticalBox::Slot()
				.HAlign(HAlign_Center)
				.AutoHeight()
				[
					Locals::MakeButton(LOCTEXT("DownButtonLabel", "Down"), FVector(0, 0, -Factor))
				]

			//--------------------------------------------------------------------------------------

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
							//.OnPressed() || .OnClicked()
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
							//.OnPressed() || .OnClicked()
						]
					]
				]
					
				/*
					SNew(SComboButton)
					.HasDownArrow(false)
				.ButtonStyle(FEditorStyle::Get(), "HoverHintOnly")
				.ForegroundColor(FSlateColor::UseForeground())
				.ContentPadding(FMargin(5, 2))
				.HAlign(HAlign_Center)
				.VAlign(VAlign_Center)
				.ButtonContent()
				[
					SNew(SHorizontalBox)

					+ SHorizontalBox::Slot()
				.AutoWidth()
				.VAlign(VAlign_Center)
				.Padding(FMargin(0, 0, 2, 0))
				[
					SNew(SImage)
					.ColorAndOpacity(FSlateColor::UseForeground())
				.Image(FEditorStyle::GetBrush("Plus"))
				]
				] */
							
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
