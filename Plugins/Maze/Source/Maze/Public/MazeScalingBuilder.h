// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MazeBuilder.h"
#include "MazeRoom.h"
#include "MazeScalingBuilder.generated.h"

USTRUCT()
struct FMazeRoomParameters {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
		FString TemplateName;
	UPROPERTY(EditAnywhere)
		FIntPoint Coordinates;
	UPROPERTY(EditAnywhere)
		FIntPoint TemplateScale;
	UPROPERTY(EditAnywhere)
		TArray<FIntPoint> ExitPoints;
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
	TArray<TSubclassOf<AMazeRoom>> RoomTemplates;
	UPROPERTY(EditAnywhere)
	TArray<FMazeRoomParameters> Rooms;
protected:
	virtual void BeginPlay() override;
public:
	virtual void BuildMaze() override;
	void BuildSingleRoom(const FMazeRoomParameters&) const;
	void BuildRooms() const;
	void BuildPaths() const;
};
