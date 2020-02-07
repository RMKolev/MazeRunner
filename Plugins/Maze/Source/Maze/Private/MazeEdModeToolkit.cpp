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

//Function called when the Create Wrapper button is clicked
FReply FMazeEdModeToolkit::OnClickedCreateWrapper()
{
	UE_LOG(Maze, Warning, TEXT("Cavebased mode."));

	UWorld* EditorWorld = GEditor->GetEditorWorldContext().World();

	//Setting a default value
	MazeWrapper = nullptr;

	//Search for already spawned Maze Wrapper
	auto It = TActorIterator<AMazeBuilderWrapper>(EditorWorld);
	for (; It; ++It)
	{
		MazeWrapper = *It;
	}

	FText MsgText;
	FString MsgString;

	//If no wrapper is already spawned, we should spawn it now
	if (MazeWrapper == nullptr)
	{
		FVector Location = FVector(0.0f);
		FRotator Rotation = FRotator(0, 0, 0);

		MazeWrapper = (AMazeBuilderWrapper*)EditorWorld->SpawnActor(AMazeBuilderWrapper::StaticClass(), &Location, &Rotation);

		FString WrapperName("Maze Wrapper");

		MazeWrapper->Rename(*WrapperName);
		MazeWrapper->SetActorLabel(*WrapperName);

		MsgString = TEXT("AMazeWrapper named Maze Wrapper was created.\nPlease configure it in the Details Panel and generate the chosen maze.");
		MsgText = FText::FromString(MsgString);

		UE_LOG(Maze, Warning, TEXT("New maze wrapper."));
	}
	//If a wrapper already exists
	else
	{
		MsgString = TEXT("AMazeWrapper already exists and is named Maze Wrapper. \nPlease configure it in the Details Panel and generate the chosen maze.");
		MsgText = FText::FromString(MsgString);

		UE_LOG(Maze, Warning, TEXT("Maze wrapper already exists."));
	}

	FText TitleText = FText::FromString(TEXT("Maze Plugin"));

	FMessageDialog::Open(EAppMsgType::Ok, MsgText, &TitleText);

	return FReply::Handled();
}

//Function called when the Generate Maze button is clicked
FReply FMazeEdModeToolkit::OnClickedGenerateMaze()
{
	//If there is no wrapper instantiated
	if (MazeWrapper == nullptr)
	{
		FText TitleText = FText::FromString(TEXT("Maze Plugin"));

		FString MsgString = TEXT("AMazeWrapper does not exists. \nPlease create an instance of it first.");
		FText  MsgText = FText::FromString(MsgString);

		FMessageDialog::Open(EAppMsgType::Ok, MsgText, &TitleText);

		UE_LOG(Maze, Warning, TEXT("Maze wrapper does not exists."));
	}

	MazeWrapper->InstantiateMazeBuilder();

	return FReply::Handled();
}

//Rendering the combo button
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
			.Text(LOCTEXT("HelperLabel", "Steps in order to create a maze:\n1. Create a wrapper class\n2. Configure the spawned wrapper in the details panel\n3. Generate a maze and enjoy! :)"))
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
						.Text(FText::FromString("Maze Generator options:"))
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
							.Text(FText::FromString("Create a wrapper class."))
							.ForegroundColor(FLinearColor(255.0f, 255.0f, 255.0f, 1.0f))
							.OnClicked(this, &FMazeEdModeToolkit::OnClickedCreateWrapper)
						]

						+ SVerticalBox::Slot()
						.AutoHeight()
						.HAlign(HAlign_Center)
						.Padding(0)
						[
							SNew(SButton)
							.ButtonColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f, 0.0f))
							.Text(FText::FromString("Generate a maze."))
							.ForegroundColor(FLinearColor(255.0f, 255.0f, 255.0f, 1.0f))
							.OnClicked(this, &FMazeEdModeToolkit::OnClickedGenerateMaze)
						]
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
