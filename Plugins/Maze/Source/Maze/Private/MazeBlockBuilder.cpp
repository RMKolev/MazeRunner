// Fill out your copyright notice in the Description page of Project Settings.


#include "MazeBlockBuilder.h"
#include "CaveGeneration.h"
#include "MazeGenerator.h"

void AMazeBlockBuilder::BuildMaze() 
{
	//FCaveGeneration CaveGen(Seed, Height, Width, FillPercentige, NumberOfIterations);
	//CaveGen.GenerateCave();

	//TArray<TArray<char>> MazeScheme;
	//CaveGen.ToAMazeRoom(MazeScheme);

	//for (int i = 0; i < Height; i++)
	//{
	//	for (int j = 0; j < Width; j++)
	//	{
	//		FVector SpawnLocation = /*GetActorLocation() +*/ FVector(i * SideOfCubeAtScaleOne * ScaleForAllMeshes.X,
	//			j * SideOfCubeAtScaleOne * ScaleForAllMeshes.Y, 0);
	//		if (Maze[i][j] == '#')
	//		{
	//			//SpawnLocation.Z = SideOfCubeAtScaleOne * ScaleForAllMeshes.Z;
	//			FTransform SpawnTransform(FRotator::ZeroRotator, SpawnLocation, ScaleForAllMeshes);
	//			//AActor* Wall = World->SpawnActor<AActor>(WallActorClass, SpawnLocation, FRotator::ZeroRotator, SpawnParameters);
	//			//Wall->SetActorScale3D(ScaleForAllMeshes);
	//			WallInstancedMesh->AddInstance(SpawnTransform);

	//		}
	//		else if (Maze[i][j] == '_') {
	//			FTransform SpawnTransform(FRotator::ZeroRotator, SpawnLocation, ScaleForAllMeshes);
	//			/*AActor * Floor = World->SpawnActor<AActor>(FloorActorClass, SpawnLocation, FRotator::ZeroRotator, SpawnParameters);
	//			Floor->SetActorScale3D(ScaleForAllMeshes);*/
	//			FloorInstancedMesh->AddInstance(SpawnTransform);
	//		}
	//	}
	//}
}

void AMazeBlockBuilder::BeginPlay()
{
	Super::BeginPlay();
	auto MGI = (AMazeGenerator*)MG.GetDefaultObject();
	MGI->BuildMaze();
	//MGI->BuildSurroundingWalls();
	BuildMazeFromScheme(MGI->GetMazeScheme());

}

void AMazeBlockBuilder::BuildMazeFromScheme(const TArray<TArray<int8>>& MazeScheme)
{
	for (int i = 0; i < MazeScheme.Num(); ++i)
	{
		for (int j = 0; j < MazeScheme[i].Num(); ++j)
		{
			if (CharacterMap.Find(MazeScheme[i][j]) != nullptr)
			{
				UE_LOG(Maze, Warning, TEXT("Building actor on coordinates %d,%d"), i, j);
				auto InstanceName = CharacterMap.FindChecked(MazeScheme[i][j]);
				if (InstanceMeshes.Find(InstanceName.InstanceMeshName) != nullptr)
				{
					auto Instance = InstanceMeshes.FindChecked(InstanceName.InstanceMeshName);
					FTransform Trans(FRotator::ZeroRotator, Basis.GetMazeActorLocation(FIntPoint(i, j), FIntVector(1, 1, MazeScheme[i][j] == 3 ? 2 : 1)), FVector(1, 1, MazeScheme[i][j] == 3 ? 2 : 1));
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
