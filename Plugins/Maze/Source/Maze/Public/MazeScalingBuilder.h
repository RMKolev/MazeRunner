// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MazeBuilder.h"
#include "MazeGenerator.h"
#include "MazeScalingBuilder.generated.h"
/**
 *
 */
UCLASS()
class MAZE_API AMazeScalingBuilder : public AMazeBuilder
{
	GENERATED_BODY()
protected:

	virtual void BeginPlay() override;
public:
	virtual void BuildMaze() override;
	virtual void BuildMazeFromScheme(TArray<TArray<int8>>);
};
