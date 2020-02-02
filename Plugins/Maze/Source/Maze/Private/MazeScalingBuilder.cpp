// Fill out your copyright notice in the Description page of Project Settings.


#include "MazeScalingBuilder.h"
#include "Engine/World.h"
#include "Maze.h"

void AMazeScalingBuilder::BeginPlay()
{
	Super::BeginPlay();

	for (auto room : rooms) {
		UE_LOG(Maze, Error, TEXT("AMazeScalingBuilder::BeginPlay() ForEach"));
		BuildSingleRoom(room);
	}
}

void AMazeScalingBuilder::BuildMaze()
{
	// TO DO;
}

void AMazeScalingBuilder::BuildSingleRoom(const TSubclassOf<AMazeRoom>& room) const
{
	UE_LOG(Maze, Error, TEXT("AMazeScalingBuilder::BuildSingleRoom(TSubclassOf<AMazeRoom> room) in func"))
	if (IsValid(world)) {
		UE_LOG(Maze, Error, TEXT("AMazeScalingBuilder::BuildSingleRoom(TSubclassOf<AMazeRoom> room) world is valid"))
			FMazePoint roomCoordinates = room.GetDefaultObject()->GetMazeCoordinates();
		for (auto component = ((AMazeRoom*)*room)->GetMazeComponentIterator(); component; ++component) {
			//if (assets.Contains(component->name)) {
				UE_LOG(Maze, Error, TEXT("AMazeScalingBuilder::BuildSingleRoom(TSubclassOf<AMazeRoom> room) in ForLoop"))
				FMazePoint localCoordinates = component->localCoordinates;
				localCoordinates = localCoordinates + roomCoordinates;
				FIntVector scale = component->scale;
				FString assetName = component->name;
				FVector location = basis.GetMazeActorLocation(localCoordinates, scale);
				world->SpawnActor<AMazeActor>(assets.FindChecked(component->name),location,FRotator::ZeroRotator);
			//}
		}
	}
}
