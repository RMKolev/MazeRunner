// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "MazeEdModeToolkit.h"
#include "MazeEdMode.h"
#include "Engine/Selection.h"
#include "Widgets/Input/SComboButton.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Images/SImage.h"
#include "EditorStyleSet.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "CoreMinimal.h"
#include "Editor/EditorEngine.h"
#include "Engine/GameEngine.h"
#include "Maze.h"
#include "Misc/MessageDialog.h"
#include "EngineUtils.h"
#include "MazeBuilderWrapper.h"
#include "EditorModeManager.h"



#define LOCTEXT_NAMESPACE "FMazeEdModeToolkit"

FMazeEdModeToolkit::FMazeEdModeToolkit()
{
}

FReply FMazeEdModeToolkit::OnClickedRoombasedWrapper()
{
	UE_LOG(Maze, Warning, TEXT("Roombased mode."));

	FText TitleText = FText::FromString(TEXT("Maze Plugin"));
	FString MsgString = TEXT("AActor named... was created.\nPlease configure it in the Details Panel and generate the chosen maze.");
	FText MsgText = FText::FromString(MsgString);

	FMessageDialog::Open(EAppMsgType::Ok, MsgText, &TitleText);

	return FReply::Handled();
}

FReply FMazeEdModeToolkit::OnClickedCavebasedWrapper()
{
	UE_LOG(Maze, Warning, TEXT("Cavebased mode."));

	UWorld* EditorWorld = GEditor->GetEditorWorldContext().World();

	FActorSpawnParameters SpawnInfo;
	FVector Location = FVector(0.0f);
	FRotator Rotation = FRotator(0, 0, 0);

	auto It = TActorIterator<AMazeBuilderWrapper>(EditorWorld);

	for (; It; ++It)
	{
		MazeWrapper = *It;
	}

	if (MazeWrapper == nullptr)
	{
		MazeWrapper = (AMazeBuilderWrapper*)EditorWorld->SpawnActor(AMazeBuilderWrapper::StaticClass(), &Location, &Rotation);

		FString WrapperName("Maze Wrapper");

		MazeWrapper->Rename(*WrapperName);
		MazeWrapper->SetActorLabel(*WrapperName);

		FText TitleText = FText::FromString(TEXT("Maze Plugin"));
		FString MsgString = TEXT("AMazeWrapper named Maze Wrapper was created.\nPlease configure it in the Details Panel and generate the chosen maze.");
		FText MsgText = FText::FromString(MsgString);

		FMessageDialog::Open(EAppMsgType::Ok, MsgText, &TitleText);

		UE_LOG(Maze, Warning, TEXT("New maze wrapper."));
	}

	return FReply::Handled();
}

FReply FMazeEdModeToolkit::OnClickedRoombasedMaze()
{
	return FReply::Handled();
}

FReply FMazeEdModeToolkit::OnClickedCavebasedMaze()
{
	MazeWrapper->InstantiateMazeBuilder();

	return FReply::Handled();
}

void FMazeEdModeToolkit::Init(const TSharedPtr<IToolkitHost>& InitToolkitHost)
{
	const float Factor = 256.0f;

	SAssignNew(ToolkitWidget, SBorder)
	.HAlign(HAlign_Center)
	.Padding(25)
	[
		SNew(SHorizontalBox)

		+SHorizontalBox::Slot()
		[
		SNew(SVerticalBox)

		+ SVerticalBox::Slot()
		  .AutoHeight()
		  .HAlign(HAlign_Center)
		  .Padding(0)
		  [
			SNew(STextBlock)
			.AutoWrapText(true)
			.Text(LOCTEXT("HelperLabel", "Steps in order to create a maze:\n1. Choose a wrapper class\n2. Configure the spawned wrapper in the details panel\n3. Click 'Generate Maze' and enjoy! :)"))
		  ]

			+ SVerticalBox::Slot()
				.HAlign(HAlign_Center)
				.AutoHeight()
				.Padding(0,10,0,50)
				[
					SNew(SComboButton)
					.ContentPadding(0)
				    .ButtonContent()
				    [
						SNew(STextBlock)
						.Text(FText::FromString("Choose a wrapper class:"))
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
							.Text(FText::FromString("Create a roombased wrapper."))
							.ForegroundColor(FLinearColor(255.0f, 255.0f, 255.0f, 1.0f))
							.OnClicked(this, &FMazeEdModeToolkit::OnClickedRoombasedWrapper)
						]

						+ SVerticalBox::Slot()
						.AutoHeight()
						.HAlign(HAlign_Center)
						.Padding(0)
						[
							SNew(SButton)
							.ButtonColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f, 0.0f))
							.Text(FText::FromString("Create a cavebased wrapper."))
							.ForegroundColor(FLinearColor(255.0f, 255.0f, 255.0f, 1.0f))
							.OnClicked(this, &FMazeEdModeToolkit::OnClickedCavebasedWrapper)
						]
					]
				]

			+ SVerticalBox::Slot()
				.HAlign(HAlign_Center)
				.AutoHeight()
				.Padding(0)
				[
					SNew(SHorizontalBox)

					+ SHorizontalBox::Slot()
					.AutoWidth()
					[
						SNew(SButton)
						.Text(FText::FromString("Generate a roombased maze"))
						.OnClicked(this, &FMazeEdModeToolkit::OnClickedRoombasedMaze)
					]

			+ SHorizontalBox::Slot()
				.AutoWidth()
				[
					SNew(SButton)
					.Text(FText::FromString("Generate a cavebased maze"))
				.OnClicked(this, &FMazeEdModeToolkit::OnClickedCavebasedMaze)
				]					
				]
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
