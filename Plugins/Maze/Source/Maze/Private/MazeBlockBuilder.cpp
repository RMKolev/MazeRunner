// Fill out your copyright notice in the Description page of Project Settings.


#include "MazeBlockBuilder.h"
#include "CaveGeneration.h"
#include "MazeGenerator.h"


void AMazeBlockBuilder::BuildMaze() 
{
	auto MGI = (AMazeGenerator*)MG.GetDefaultObject();
	MGI->BuildMaze();
	BuildMazeFromScheme(MGI->GetMazeScheme());
}

void AMazeBlockBuilder::BeginPlay()
{
	Super::BeginPlay();

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
