// Fill out your copyright notice in the Description page of Project Settings.

#include "MazeRoom.h"
#include "Maze.h"
#include "..\Public\MazeRoom.h"


// Sets default values
AMazeRoom::AMazeRoom()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AMazeRoom::GenerateWalls(const FIntPoint& RoomSize, const TArray<FIntPoint>& ExitPoints)
{
	//Components.Empty();
	UE_LOG(Maze, Warning, TEXT("AMazeRoom::GenerateWalls -> starting Wall generation"));
	if (bGenerateWalls) {
		FMazeActorParameters Wall = FMazeActorParameters(FString("Wall"), FIntVector(0, 1, 2), FIntPoint(0, 0),false);
		for (int32 i = 0; i < RoomSize.X - 1; ++i) {
			bool Clear = true;
			for (auto Exit : ExitPoints) {
				if (Exit.X == i && Exit.Y == 0) Clear = false;
			}
			if (Clear) {
				Wall.Scale.X++;
			}
			else {
				if (Wall.Scale.X != 0) {
					UE_LOG(Maze, Warning, TEXT("Adding Wall %s, size %d"), *Wall.LocalCoordinates.ToString(),Wall.Scale.X)
					Components.Add(Wall);
				}
				Wall = FMazeActorParameters(FString("Wall"), FIntVector(0, 1, 2), FIntPoint(i+1, 0),false);
			}
		}
		if (Wall.Scale.X != 0) {
			UE_LOG(Maze, Warning, TEXT("Adding Wall after arr %s, size %d"), *Wall.LocalCoordinates.ToString(), Wall.Scale.X)
			Components.Add(Wall);
		}
		for (int32 i = 0; i < RoomSize.Y - 1; ++i) {

		}
	}
	else {
		UE_LOG(Maze, Warning, TEXT("AMazeRoom::GenerateWalls -> bGenerateWalls is false"));
	}
}
/*
AMazeRoom::AMazeRoom(const FString& Name, const TArray<FMazeActorParameters>& Components, const TArray<FIntPoint>& ExitPoints)
	: RoomName(Name), Components(Components), ExitPoints(ExitPoints)
{
}*/


// Called when the game starts or when spawned
void AMazeRoom::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMazeRoom::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

