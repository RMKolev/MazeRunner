// Fill out your copyright notice in the Description page of Project Settings.


#include "MazeScalingBuilder.h"
#include "Engine/World.h"
#include "Maze.h"
#include "GameFramework/PlayerStart.h"
#include "EngineUtils.h"

void AMazeScalingBuilder::BeginPlay()
{
	Super::BeginPlay();
}

void AMazeScalingBuilder::BuildMaze()
{
	if (this->MazeScheme.Num() == 0)
	{
		UE_LOG(Maze, Error, TEXT("MazeScalingBuilder:BuildMaze() - MazeScheme is not initialised or empty!"));
		return;
	}
	BuildMazeFromScheme(this->MazeScheme);
}
void AMazeScalingBuilder::BuildMazeFromScheme( TArray<TArray<int8>> MazeScheme)
{
	for (int i = 0; i < MazeScheme.Num(); ++i)
	{
		for (int j = 0; j < MazeScheme[i].Num(); ++j)
		{
			if (MazeScheme[i][j] != 0)
			{

				if (CharacterMap.Find(MazeScheme[i][j]) != nullptr)
				{
					//UE_LOG(Maze, Warning, TEXT("Building actor on coordinates %d,%d"), i, j);
					auto ComponentInformation = CharacterMap.FindChecked(MazeScheme[i][j]);
					auto InstanceName = ComponentInformation.InstanceMeshName;
					if (InstanceMeshes.Find(InstanceName) != nullptr)
					{
						int8 ID = MazeScheme[i][j];
						int32 NumberRight = 0;
						int32 NumberDown = 0;
						bool bContinueRight = true;
						bool bContinueDown = true;
						while (bContinueRight || bContinueDown)
						{
							if (i+NumberDown >= MazeScheme.Num() )
							{
								bContinueDown = false;
							}
							if (j + NumberRight >= MazeScheme[i].Num())
							{
								bContinueRight = false;
							}
							if (bContinueRight)
							{
								for (int k = i; k < i + NumberDown && k < MazeScheme.Num(); ++k)
								{
									if (MazeScheme[k][j + NumberRight] != ID)
									{
										bContinueRight = false;
										break;
									}
								}
								if (bContinueRight)
								{
									NumberRight++;
								}
							}
							if (bContinueDown)
							{
								for (int k = j; k < j + NumberRight && k < MazeScheme[i].Num(); ++k)
								{
									if (MazeScheme[i+NumberDown][k] != ID)
									{
										bContinueDown = false;
										break;
									}
								}
								if (bContinueDown)
								{
									NumberDown++;
								}
							}
						}
						for (int k = i; k < i + NumberDown; ++k)
						{
							for (int l = j; l < j + NumberRight; ++l)
							{
								MazeScheme[k][l] = 0;
							}
						}

						UE_LOG(Maze, Log, TEXT("Building Maze Component with size:%d,%d on Coordinates %d,%d"), NumberRight, NumberDown, i, j);

						auto Instance = InstanceMeshes.FindChecked(InstanceName);
						FIntVector InstanceScaleInt = FIntVector(ComponentInformation.Scale.X * (NumberDown), ComponentInformation.Scale.Y * (NumberRight), ComponentInformation.Scale.Z);
						FVector InstanceScale = FVector(ComponentInformation.Scale.X * Basis.Scale.X* (NumberDown), ComponentInformation.Scale.Y * Basis.Scale.Y * (NumberRight), ComponentInformation.Scale.Z * Basis.Scale.Z);
						FTransform Trans(FRotator::ZeroRotator, Basis.GetMazeComponentLocation(FIntPoint(i, j), InstanceScaleInt), InstanceScale);
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
}