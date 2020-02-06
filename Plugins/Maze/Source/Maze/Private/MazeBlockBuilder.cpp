// Fill out your copyright notice in the Description page of Project Settings.


#include "MazeBlockBuilder.h"
#include "CaveGeneration.h"

void AMazeBlockBuilder::BuildMaze() 
{
	FCaveGeneration CaveGen(Seed, Height, Width, FillPercentige, NumberOfIterations);
	CaveGen.GenerateCave();

	TArray<TArray<char>> Maze;
	CaveGen.ToAMazeRoom(Maze);

	for (int i = 0; i < Height; i++)
	{
		for (int j = 0; j < Width; j++)
		{
			FVector SpawnLocation = /*GetActorLocation() +*/ FVector(i * SideOfCubeAtScaleOne * ScaleForAllMeshes.X,
				j * SideOfCubeAtScaleOne * ScaleForAllMeshes.Y, 0);
			if (Maze[i][j] == '#')
			{
				//SpawnLocation.Z = SideOfCubeAtScaleOne * ScaleForAllMeshes.Z;
				FTransform SpawnTransform(FRotator::ZeroRotator, SpawnLocation, ScaleForAllMeshes);
				//AActor* Wall = World->SpawnActor<AActor>(WallActorClass, SpawnLocation, FRotator::ZeroRotator, SpawnParameters);
				//Wall->SetActorScale3D(ScaleForAllMeshes);
				WallInstancedMesh->AddInstance(SpawnTransform);

			}
			else if (Maze[i][j] == '_') {
				FTransform SpawnTransform(FRotator::ZeroRotator, SpawnLocation, ScaleForAllMeshes);
				/*AActor * Floor = World->SpawnActor<AActor>(FloorActorClass, SpawnLocation, FRotator::ZeroRotator, SpawnParameters);
				Floor->SetActorScale3D(ScaleForAllMeshes);*/
				FloorInstancedMesh->AddInstance(SpawnTransform);
			}
		}
	}
}
