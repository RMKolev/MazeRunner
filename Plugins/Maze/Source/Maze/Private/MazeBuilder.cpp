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

FIntPoint AMazeBuilder::GetRandomWalkablePoint(FRandomStream& RStream)
{
	for (int Tries = 500; Tries > 0; --Tries)
	{
		int X = RStream.RandRange(0, WalkableTerrain.Num() - 1);
		int Y = RStream.RandRange(0, WalkableTerrain[X].Num() - 1);
		if (WalkableTerrain[X][Y])
		{
			UE_LOG(Maze, Log, TEXT("AMazeRoomGenerator: GetRandomCharacterStartingPoint - Character"))
				return FIntPoint(X, Y);
		}
	}
	// There is a chance after 500 tries the algorithm hasn't found a valid point, so a guaranteed approach is used
	int NumberTries = RStream.RandRange(30, 300);
	FIntPoint Result = FIntPoint(0, 0);
	for (int i = 0; i < WalkableTerrain.Num(); ++i)
	{
		for (int j = 0; j < WalkableTerrain[i].Num(); ++j)
		{
			if (WalkableTerrain[i][j])
			{
				Result = FIntPoint(i, j);
				NumberTries--;
				if (NumberTries <= 0)
				{
					return Result;
				}
			}
		}
	}
	return Result;
}

// Called when the game starts or when spawned
void AMazeBuilder::BeginPlay()
{
	Super::BeginPlay();

	if (bGenerateOnPlay)
	{
		GenerateMaze();
	}
	if (bBuildOnPlay)
	{
		RegisterInstanceMeshComponents();
		BuildMaze();
		PlaceActors();
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
				PS->SetActorLocation(Basis.GetMazeActorLocation(CharacterStartPoint,FIntVector(1,1,1)));
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
	MGInstance->BuildMaze();
	UE_LOG(Maze, Log, TEXT("AMazeBuilder: Maze successfully generated"));
	this->MazeScheme = MGInstance->GetMazeScheme();
	this->WorldSeed = MGInstance->GetSeed();
	this->WalkableTerrain = MGInstance->GetWalkableTerrain();
	this->CharacterStartPoint = MGInstance->GetRandomCharacterStartingPoint();
}

void AMazeBuilder::PlaceActors()
{
	this->ActorsToPlace.Sort([](FMazeActor First, FMazeActor Second)
							 {
								 return First.Priority < Second.Priority;
							 });
	int32 SpaceCount = 0;
	for (int i = 0; i < WalkableTerrain.Num(); ++i)
	{
		for (int j = 0; j < WalkableTerrain[i].Num(); ++j)
		{
			if (WalkableTerrain[i][j])
			{
				++SpaceCount;
			}
		}
	}
	FRandomStream RS = FRandomStream(WorldSeed);
	FIntPoint Point = GetRandomWalkablePoint(RS);
	auto World = GetWorld();
	if (IsValid(World))
	{
		UE_LOG(Maze, Error, TEXT("MazeBuilder : PlaceActors -> World is invalid!"));
	}
	for (FMazeActor Actor : ActorsToPlace)
	{
		for (int i = 0; i < Actor.Quantity && SpaceCount>0;++i)
		{
			if (Point != CharacterStartPoint)
			{
				WalkableTerrain[Point.X][Point.Y] = false;
				UE_LOG(Maze, Warning, TEXT("Spawning Actor on %d,%d"), Point.X, Point.Y);
				SpaceCount--;
				auto AssetClass = Actor.Asset;
				auto Instance = World->SpawnActor<AActor>(AssetClass,Basis.GetMazeActorLocation(Point, FIntVector(1, 1, 1)),FRotator::ZeroRotator);
				Instance->SetActorScale3D(Actor.Scale);
				Point = GetRandomWalkablePoint(RS);
			}
		}
	}
	UE_LOG(Maze, Log, TEXT("Free Space Count:%d"), SpaceCount);
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

