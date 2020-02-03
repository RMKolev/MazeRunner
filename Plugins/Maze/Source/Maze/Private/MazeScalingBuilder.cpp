// Fill out your copyright notice in the Description page of Project Settings.


#include "MazeScalingBuilder.h"
#include "Engine/World.h"
#include "Maze.h"

void AMazeScalingBuilder::BeginPlay()
{
	Super::BeginPlay();
	for (auto room : rooms) {
			UE_LOG(Maze, Log, TEXT("AMazeScalingBuilder::BeginPlay() ForEach"));
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
			if (t.GetDefaultObject()->GetMazeRoomName().Equals(room.templateName)) {
				return true;
			}
			return false;
			});
		if (roomTemplate == nullptr) {
			UE_LOG(Maze, Error, TEXT("MazeScalingBuilder: Room Template was not found - %s"), *room.templateName);
		}
		else {
			auto roomInstance = roomTemplate->GetDefaultObject();
			roomInstance->GenerateWalls(room.templateScale,room.exitPoints);
			auto assetIterator = roomInstance->GetMazeComponentIterator();
			for(assetIterator;assetIterator;assetIterator++){
				auto assetTemplate = this->assets.Find(assetIterator->name);
				if (assetTemplate == nullptr) {
					UE_LOG(Maze, Error, TEXT("MazeScalingBuilder: I should build an object, but there is no template with this name"));
				}
				else {
					auto assetInstance = assetTemplate->GetDefaultObject();
					auto actorScale = assetIterator->bScale ? FVector(FIntVector(room.templateScale.X * assetIterator->scale.X, room.templateScale.Y * assetIterator->scale.Y, 1 * assetIterator->scale.Z)):FVector(assetIterator->scale);
					FVector coordinates = this->basis.GetMazeActorLocation(room.coordinates + assetIterator->localCoordinates, FIntVector(actorScale));
					instanceMeshes.FindChecked(assetIterator->name)->AddInstanceWorldSpace(FTransform(FRotator::ZeroRotator, coordinates, actorScale));
					UE_LOG(Maze, Warning, TEXT("This is my %s coordinates"), *coordinates.ToString());
				}
			}
		}
		
		
		
		/*for (auto component = room->GetMazeComponentIterator(); component; ++component) {
			//if (assets.Contains(component->name)) {
				UE_LOG(Maze, Error, TEXT("AMazeScalingBuilder::BuildSingleRoom(TSubclassOf<AMazeRoom> room) in ForLoop"))
				FIntPoint localCoordinates = component->localCoordinates;
				localCoordinates = localCoordinates + roomCoordinates;
				FIntVector scale = component->scale;
				FString assetName = component->name;
				FVector location = basis.GetMazeActorLocation(localCoordinates, scale);
				world->SpawnActor<AMazeActor>(assets.FindChecked(component->name),location,FRotator::ZeroRotator);
			//}*/
	}
}