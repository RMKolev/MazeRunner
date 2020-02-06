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
				auto InstanceName = CharacterMap.FindChecked(MazeScheme[i][j]);
				if (InstanceMeshes.Find(InstanceName) != nullptr)
				{
					auto Instance = InstanceMeshes.FindChecked(InstanceName);
					FTransform Trans( FRotator::ZeroRotator,Basis.GetMazeActorLocation(FIntPoint(i, j), FIntVector(2, 2, MazeScheme[i][j] == 3 ? 2 : 1)), FVector(2,2, MazeScheme[i][j]==3?2:1));
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