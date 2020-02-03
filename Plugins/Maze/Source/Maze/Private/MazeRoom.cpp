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

void AMazeRoom::GenerateWalls(const FIntPoint& roomSize, const TArray<FIntPoint>& exitPoints)
{
	//components.Empty();
	UE_LOG(Maze, Warning, TEXT("AMazeRoom::GenerateWalls -> starting wall generation"));
	if (bGenerateWalls) {
		FMazeActorParameters wall = FMazeActorParameters(FString("Wall"), FIntVector(0, 1, 2), FIntPoint(0, 0),false);
		for (int32 i = 0; i < roomSize.X - 1; ++i) {
			bool clear = true;
			for (auto exit : exitPoints) {
				if (exit.X == i && exit.Y == 0) clear = false;
			}
			if (clear) {
				wall.scale.X++;
			}
			else {
				if (wall.scale.X != 0) {
					UE_LOG(Maze, Warning, TEXT("Adding wall %s, size %d"), *wall.localCoordinates.ToString(),wall.scale.X)
					components.Add(wall);
				}
				wall = FMazeActorParameters(FString("Wall"), FIntVector(0, 1, 2), FIntPoint(i+1, 0),false);
			}
		}
		if (wall.scale.X != 0) {
			UE_LOG(Maze, Warning, TEXT("Adding wall after arr %s, size %d"), *wall.localCoordinates.ToString(), wall.scale.X)
			components.Add(wall);
		}
		for (int32 i = 0; i < roomSize.Y - 1; ++i) {

		}
	}
	else {
		UE_LOG(Maze, Warning, TEXT("AMazeRoom::GenerateWalls -> bGenerateWalls is false"));
	}
}
/*
AMazeRoom::AMazeRoom(const FString& name, const TArray<FMazeActorParameters>& components, const TArray<FIntPoint>& exitPoints)
	: roomName(name), components(components), exitPoints(exitPoints)
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

