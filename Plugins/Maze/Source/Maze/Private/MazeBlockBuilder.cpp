// Fill out your copyright notice in the Description page of Project Settings.


#include "MazeBlockBuilder.h"
#include "MazeGenerator.h"

void AMazeBlockBuilder::BuildMaze() 
{
	
	BuildMazeFromScheme(this->MazeScheme);
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
				auto ComponentInformation = CharacterMap.FindChecked(MazeScheme[i][j]);
				auto InstanceName = ComponentInformation.InstanceMeshName;
				auto Instance = InstanceMeshes.FindChecked(InstanceName);
				FIntVector InstanceScaleInt = FIntVector(ComponentInformation.Scale.X, ComponentInformation.Scale.Y, ComponentInformation.Scale.Z);
				FVector InstanceScale = FVector(ComponentInformation.Scale.X * Basis.Scale.X, ComponentInformation.Scale.Y * Basis.Scale.Y, ComponentInformation.Scale.Z * Basis.Scale.Z);
				FTransform Trans(FRotator::ZeroRotator, Basis.GetMazeComponentLocation(FIntPoint(i, j), InstanceScaleInt), InstanceScale);
				Instance->AddInstanceWorldSpace(Trans);
			
			}
			else
			{
				UE_LOG(Maze, Error, TEXT("No valid component exists for this code: %d"), MazeScheme[i][j]);
			}
		}
	}
}
