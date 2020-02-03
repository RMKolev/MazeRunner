// Fill out your copyright notice in the Description page of Project Settings.

#include "MazeProceduralRoom.h"

void AMazeProceduralRoom::BeginPlay()
{
	Super::BeginPlay();
}

void AMazeProceduralRoom::ConfigureWalls()
{
	
}

void AMazeProceduralRoom::ConfigureFloor()
{
	this->components.Add(
		FMazeActorParameters(FString("Floor"),
			FIntVector(size.X, size.Y, 1),
			FIntPoint(0, 0)));
}
void AMazeProceduralRoom::Configure()
{
	ConfigureFloor();
	ConfigureWalls();
}

