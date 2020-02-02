// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MazeBuilder.h"
#include "MazeRoom.h"
#include "Rectangle.h"
#include "MazeScalingBuilder.generated.h"

/**
 * 
 */
UCLASS()
class MAZE_API AMazeScalingBuilder : public AMazeBuilder
{
	GENERATED_BODY()
private:
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<AMazeRoom>> rooms;
protected:
	virtual void BeginPlay() override;
public:
	virtual void BuildMaze() override;
	void BuildSingleRoom(const TSubclassOf<AMazeRoom>&) const;
	void BuildRooms() const;
	void BuildPaths() const;
};
