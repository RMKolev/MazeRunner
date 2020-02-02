// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MazeBuilder.h"
#include "MazeRoom.h"
#include "Rectangle.h"
#include "MazeScalingBuilder.generated.h"

USTRUCT()
struct FMazeRoomParameters {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
		FString templateName;
	UPROPERTY(EditAnywhere)
		FMazePoint coordinates;
	UPROPERTY(EditAnywhere)
		FMazePoint templateScale;
};
/**
 * 
 */
UCLASS()
class MAZE_API AMazeScalingBuilder : public AMazeBuilder
{
	GENERATED_BODY()
private:
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<AMazeRoom>> roomTemplates;
	UPROPERTY(EditAnywhere)
	TArray<FMazeRoomParameters> rooms;
protected:
	virtual void BeginPlay() override;
public:
	virtual void BuildMaze() override;
	void BuildSingleRoom(const FMazeRoomParameters&) const;
	void BuildRooms() const;
	void BuildPaths() const;
};
