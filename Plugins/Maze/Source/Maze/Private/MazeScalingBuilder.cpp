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

	TArray<AActor*> AttachedActors;
	this->GetAttachedActors(AttachedActors);
	UE_LOG(Maze, Warning, TEXT("AMazeScalingBuilder::BeginPlay() Num of attatched actors: %d"), AttachedActors.Num());

	for (auto temp : RoomTemplates)
	{
		auto actor = World->SpawnActor<AMazeRoom>(temp, FVector(100, 100, 317.4), FRotator::ZeroRotator);
		actor->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform, TEXT("Test Room"));
		UE_LOG(Maze, Warning, TEXT("AMazeScalingBuilder::BeginPlay() actor name: %s"), *actor->GetName());
	}

	//TArray<AActor*> AttachedActors;
	this->GetAttachedActors(AttachedActors);
	UE_LOG(Maze, Warning, TEXT("AMazeScalingBuilder::BeginPlay() Num of attatched actors: %d"), AttachedActors.Num());
	for (auto Actor : AttachedActors)
	{
		TArray<UInstancedStaticMeshComponent*> comps;
		Actor->GetComponents<UInstancedStaticMeshComponent>(comps);

		UE_LOG(Maze, Warning, TEXT("AMazeScalingBuilder::BeginPlay() Num of comps: %d"), comps.Num());
		for(int i = 0; i < comps.Num(); ++i)
		{
			UE_LOG(Maze, Warning, TEXT("AMazeScalingBuilder::BeginPlay() %s"), *comps[i]->GetName());
			
		}
	}

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