// Fill out your copyright notice in the Description page of Project Settings.


#include "MazeBuilderWrapper.h"
#include "MazeBuilder.h"
#include "Misc/MessageDialog.h"
#include "EngineUtils.h"
#include "GameFramework/Character.h"
#include "Maze.h"

// Sets default values
AMazeBuilderWrapper::AMazeBuilderWrapper()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Default value 
	MazeBuilderClass = nullptr;
}

void AMazeBuilderWrapper::InstantiateMazeBuilder()
{
	//If no blueprint is passed to the wrapper
	if (MazeBuilderClass == nullptr)
	{
		//Error message
		FText TitleText = FText::FromString(TEXT("Maze Plugin"));
		FString MsgString = TEXT("AMazeBuilder blueprint class was not specified in the Details Panel.\nPlease add it.");
		FText  MsgText = FText::FromString(MsgString);

		FMessageDialog::Open(EAppMsgType::Ok, MsgText, &TitleText);

		UE_LOG(Maze, Warning, TEXT("Blueprint class missing."));
	}
	else {

		FVector Location = FVector(0.0f);
		FRotator Rotation = FRotator(0, 0, 0);
		AMazeBuilder* MBInstance = (AMazeBuilder*)GetWorld()->SpawnActor(MazeBuilderClass, &Location, &Rotation);

		FString MazeName("Maze Builder");
		MBInstance->Rename(*MazeName);
		MBInstance->SetActorLabel(*MazeName);

		if (MBInstance->GetGenerateOnPlay() == false)
		{
			MBInstance->GenerateMaze();
		}
		if (MBInstance->GetBuildOnPlay() == false)
		{
			MBInstance->RegisterInstanceMeshComponents();
			MBInstance->RegisterAllComponents();
			MBInstance->BuildMaze();
			MBInstance->PlaceActors();
			bSpawnCharacter = true;
			CharacterName = MBInstance->GetCharacterName();
			CharacterLocation = MBInstance->GetCharacterStartingLocation();
		}

		//Message that the maze is generated
		FText TitleText = FText::FromString(TEXT("Maze Plugin"));
		FString MsgString = TEXT("AMazeBuilder was instantiated.");
		FText  MsgText = FText::FromString(MsgString);

		FMessageDialog::Open(EAppMsgType::Ok, MsgText, &TitleText);

		UE_LOG(Maze, Log, TEXT("A maze builder instantiated."));
	}
}

// Called when the game starts or when spawned
void AMazeBuilderWrapper::BeginPlay()
{
	Super::BeginPlay();

	if (bSpawnCharacter)
	{
		UE_LOG(Maze, Error, TEXT(" HEREEEEEE!"));
		if (GetWorld() != nullptr)
		{
			UE_LOG(Maze, Error, TEXT(" HEREEEEEE!"));
			UWorld* World = GetWorld();
			auto It = TActorIterator<ACharacter>(World);
			for (; It; ++It)
			{
				auto PS = *It;
				if (PS->GetName() == CharacterName)
				{
					UE_LOG(Maze, Error, TEXT(" HEREEEEEE!"));
					PS->SetActorLocation(CharacterLocation);
				}
				UE_LOG(Maze, Warning, TEXT("Here! %s"), *PS->GetName());
			}
			UE_LOG(Maze, Warning, TEXT("Character starting location %s"), *CharacterLocation.ToString());
		}
	}
}

// Called every frame
void AMazeBuilderWrapper::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

