// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MazeRoom.h"
#include "MazeProceduralRoom.generated.h"

/**
 *
 */
UCLASS()
class MAZE_API AMazeProceduralRoom : public AMazeRoom
{
	GENERATED_BODY()
protected:
	UPROPERTY(Category = RoomProperties, Editanywhere)
		FIntPoint size;
	virtual void BeginPlay() override;
	virtual void ConfigureWalls();
	virtual void ConfigureFloor();
public:
	virtual void Configure();
};