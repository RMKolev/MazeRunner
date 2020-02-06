// Fill out your copyright notice in the Description page of Project Settings.


#include "MazeScalingBuilder.h"
#include "Engine/World.h"
#include "Maze.h"

void AMazeScalingBuilder::BeginPlay()
{
	Super::BeginPlay();
	auto MGI = (AMazeRoomGenerator*)MG->GetDefaultObject();
	MGI->BuildMaze();
	MGI->BuildSurroundingWalls();
	BuildMazeFromScheme(MGI->GetMazeScheme());
	MGI->LogMazeScheme();
	auto Arr = MGI->GetWalkableTerrain();
	FString p;
	for (auto T : Arr)
	{
		for (auto Q : T)
			p.AppendInt(Q);
		p.AppendChar('\n');
	}
	UE_LOG(Maze, Warning, TEXT("Passable terrain \n%s"), *p);
}

void AMazeScalingBuilder::BuildMaze()
{
	// TO DO;
}

void AMazeScalingBuilder::BuildMazeFromScheme(const TArray<TArray<int8>>& MazeScheme)
{
	UE_LOG(Maze, Error, TEXT("HERE! %d"),MazeScheme.Num());
	for (int i = 0; i < MazeScheme.Num(); ++i)
	{
		for (int j = 0; j < MazeScheme[i].Num(); ++j)
		{
			if (CharacterMap.Find(MazeScheme[i][j]) != nullptr)
			{
				UE_LOG(Maze, Warning, TEXT("Building actor on coordinates %d,%d"), i, j);
				auto ComponentInformation = CharacterMap.FindChecked(MazeScheme[i][j]);
				auto InstanceName = ComponentInformation.InstanceMeshName;
				if (InstanceMeshes.Find(InstanceName) != nullptr)
				{
					auto Instance = InstanceMeshes.FindChecked(InstanceName);
					FVector InstanceScale = FVector(ComponentInformation.Scale.X*Basis.Scale.X, ComponentInformation.Scale.Y * Basis.Scale.Y, ComponentInformation.Scale.Z * Basis.Scale.Z);
					FTransform Trans( FRotator::ZeroRotator,Basis.GetMazeActorLocation(FIntPoint(i, j),ComponentInformation.Scale),InstanceScale);
					Instance->AddInstanceWorldSpace(Trans);
				}
			}
			else
			{
				UE_LOG(Maze, Error, TEXT("No valid component exists for this code: %d"), MazeScheme[i][j]);
			}
		}
	}
}