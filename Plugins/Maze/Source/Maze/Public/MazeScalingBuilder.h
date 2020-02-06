// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MazeBuilder.h"
#include "MazeRoom.h"
#include "MazeRoomGenerator.h"
#include "MazeScalingBuilder.generated.h"
/**
 *
 */
UCLASS()
class MAZE_API AMazeScalingBuilder : public AMazeBuilder
{
	GENERATED_BODY()
protected:
	UPROPERTY(Category = MazeAlgorithm,EditAnywhere)
		TSubclassOf<AMazeRoomGenerator> MG;

	virtual void BeginPlay() override;
public:
	virtual void BuildMaze() override;
	virtual void BuildMazeFromScheme(const TArray<TArray<int8>>&);
	//void BuildSingleRoom(const FMazeRoomParameters&) const;
	void BuildRooms() const;
	void BuildPaths() const;
};
