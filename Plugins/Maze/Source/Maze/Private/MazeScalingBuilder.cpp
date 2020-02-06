// Fill out your copyright notice in the Description page of Project Settings.


#include "MazeScalingBuilder.h"
#include "Engine/World.h"
#include "Maze.h"

void AMazeScalingBuilder::BeginPlay()
{
	Super::BeginPlay();
	for (auto Room : Rooms) {
			UE_LOG(Maze, Log, TEXT("AMazeScalingBuilder::BeginPlay() ForEach"));
			BuildSingleRoom(Room);
	}

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

void AMazeScalingBuilder::BuildSingleRoom(const FMazeRoomParameters& Room) const
{
	UE_LOG(Maze, Error, TEXT("AMazeScalingBuilder::BuildSingleRoom(TSubclassOf<AMazeRoom> Room) in func"))
	if (IsValid(World)) {
		auto RoomTemplate = RoomTemplates.FindByPredicate([&Room](const TSubclassOf<AMazeRoom> MR) {
			if (MR.GetDefaultObject()->GetMazeRoomName().Equals(Room.TemplateName)) {
				return true;
			}
			return false;
			});
		if (RoomTemplate == nullptr) {
			UE_LOG(Maze, Error, TEXT("MazeScalingBuilder: Room Template was not found - %s"), *Room.TemplateName);
		}
		else {
			auto RoomInstance = RoomTemplate->GetDefaultObject();
			RoomInstance->GenerateWalls(Room.TemplateScale,Room.ExitPoints);
			auto AssetIterator = RoomInstance->GetMazeComponentIterator();
			for(AssetIterator;AssetIterator;AssetIterator++){
				auto AssetTemplate = this->Assets.Find(AssetIterator->Name);
				if (AssetTemplate == nullptr) {
					UE_LOG(Maze, Error, TEXT("MazeScalingBuilder: I should build an object, but there is no template with this Name"));
				}
				else {
					auto AssetInstance = AssetTemplate->GetDefaultObject();
					auto ActorScale = AssetIterator->bScale ? FVector(FIntVector(Room.TemplateScale.X * AssetIterator->Scale.X, Room.TemplateScale.Y * AssetIterator->Scale.Y, 1 * AssetIterator->Scale.Z)):FVector(AssetIterator->Scale);
					FVector Coordinates = this->Basis.GetMazeActorLocation(Room.Coordinates + AssetIterator->LocalCoordinates, FIntVector(ActorScale));
					InstanceMeshes.FindChecked(AssetIterator->Name)->AddInstanceWorldSpace(FTransform(FRotator::ZeroRotator, Coordinates, ActorScale));
					UE_LOG(Maze, Warning, TEXT("This is my %s Coordinates"), *Coordinates.ToString());
				}
			}
		}
	}
}