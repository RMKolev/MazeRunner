// Fill out your copyright notice in the Description page of Project Settings.


#include "MazeBuilder.h"
#include "Engine/World.h"

#include "EngineUtils.h"
#include "GameFramework/Character.h"
#include "Maze.h"
#include "Components/CapsuleComponent.h"
#include <EditorModeManager.h>

// Sets default values
AMazeBuilder::AMazeBuilder()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AMazeBuilder::BeginPlay()
{
	Super::BeginPlay();

	if (bGenerateOnPlay)
	{
		this->GenerateMaze();
	}
	if (bBuildOnPlay)
	{
		this->RegisterInstanceMeshComponents();
		this->BuildMaze();
	}
	if (GetWorld() != nullptr)
	{
		UWorld* World = GetWorld();
		auto It = TActorIterator<ACharacter>(World);
		for (;It;++It)
		{
			auto PS = *It;
			if (PS->GetName() == CharacterName.ToString())
			{
				PS->SetActorLocation(CharacterStartPoint);
			}
			UE_LOG(Maze, Warning, TEXT("Here! %s"), *PS->GetName());
		}
		UE_LOG(Maze,Warning, TEXT("Character starting location %s"), *this->CharacterStartPoint.ToString())
	}
}

void AMazeBuilder::GenerateMaze()
{
	if(MazeGenerator == nullptr){
		UE_LOG(Maze, Error, TEXT("AMazeBuilder: Invalid Maze Generation class/blueprint"));
	}
	auto MGInstance = (AMazeGenerator*)MazeGenerator->GetDefaultObject();
	MGInstance->SetCharacterMap(this->CharacterMap);
	MGInstance->BuildMaze();
	UE_LOG(Maze, Log, TEXT("AMazeBuilder: Maze successfully generated"));
	this->MazeScheme = MGInstance->GetMazeScheme();
	this->CharacterStartPoint = Basis.GetMazeActorLocation(MGInstance->GetRandomCharacterStartingPoint(),FIntVector(1,1,1));
}

void AMazeBuilder::RegisterInstanceMeshComponents()
{
	for (auto Instance : Assets)
	{
		auto Val = NewObject<UInstancedStaticMeshComponent>(this, Instance.Value);
		Val->RegisterComponent();
		InstanceMeshes.Add(Instance.Key, Val);
	}
}

// Called every frame
void AMazeBuilder::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMazeBuilder::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	this->InstanceMeshes.Empty();
	Super::EndPlay(EndPlayReason);
}

