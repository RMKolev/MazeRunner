// Fill out your copyright notice in the Description page of Project Settings.


#include "MazeScalingBuilder.h"
#include "Engine/World.h"
#include "Maze.h"

void AMazeScalingBuilder::BeginPlay()
{
	Super::BeginPlay();
	for (auto room : rooms) {
			UE_LOG(Maze, Error, TEXT("AMazeScalingBuilder::BeginPlay() ForEach"));
			BuildSingleRoom(room);
	}
}

void AMazeScalingBuilder::BuildMaze()
{
	// TO DO;
}

void AMazeScalingBuilder::BuildSingleRoom(const FMazeRoomParameters& room) const
{
	UE_LOG(Maze, Error, TEXT("AMazeScalingBuilder::BuildSingleRoom(TSubclassOf<AMazeRoom> room) in func"))
	if (IsValid(world)) {
		auto roomTemplate = roomTemplates.FindByPredicate([&room](const TSubclassOf<AMazeRoom> t) {
			if (t.GetDefaultObject()->GetName().Equals(room.templateName)) {
				return true;
			}
			return false;
			});
		if (roomTemplate == nullptr) {
			UE_LOG(Maze, Error, TEXT("MazeScalingBuilder: Room Template was not found"));
		}
		else {
			auto roomInstance = roomTemplate->GetDefaultObject();
			auto assetIterator = roomInstance->GetMazeComponentIterator();
			for(assetIterator;assetIterator;assetIterator++){
				auto assetTemplate = this->assets.Find(assetIterator->name);
				if (assetTemplate == nullptr) {
					UE_LOG(Maze, Error, TEXT("MazeScalingBuilder: I should build an object, but there is no template with this name"));
				}
				else {
					auto assetInstance = assetTemplate->GetDefaultObject();
					FVector coordinates = this->basis.GetMazeActorLocation(room.coordinates, assetIterator->scale);
					//if(this->GetComponentByClass())
					//FTransform spawnTransform(FRotator::ZeroRotator);
				}
			}
		}
		
		
		
		/*for (auto component = room->GetMazeComponentIterator(); component; ++component) {
			//if (assets.Contains(component->name)) {
				UE_LOG(Maze, Error, TEXT("AMazeScalingBuilder::BuildSingleRoom(TSubclassOf<AMazeRoom> room) in ForLoop"))
				FMazePoint localCoordinates = component->localCoordinates;
				localCoordinates = localCoordinates + roomCoordinates;
				FIntVector scale = component->scale;
				FString assetName = component->name;
				FVector location = basis.GetMazeActorLocation(localCoordinates, scale);
				world->SpawnActor<AMazeActor>(assets.FindChecked(component->name),location,FRotator::ZeroRotator);
			//}*/
	}
}
