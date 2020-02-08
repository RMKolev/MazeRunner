// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MazeBuilder.h"
#include "MazeBlockBuilder.generated.h"

/**
 * 
 */
UCLASS()
class MAZE_API AMazeBlockBuilder : public AMazeBuilder
{
	GENERATED_BODY()
	
public:
	void BuildMaze() override;
	void BeginPlay() override;
	void BuildMazeFromScheme(const TArray<TArray<int8>>& MazeScheme);

private:
	float SideOfCubeAtScaleOne = 100.f;
};
