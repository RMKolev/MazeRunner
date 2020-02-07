// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Maze.h"
#include "MazeGenerator.generated.h"

USTRUCT()
struct FMazeProperties
{
	GENERATED_BODY();
	UPROPERTY(EditAnywhere)
		FName ComponentName;
	UPROPERTY(EditAnywhere)
		FName InstanceMeshName;
	UPROPERTY(EditAnywhere)
		FIntVector Scale;
	UPROPERTY(EditAnywhere)
		int8 Id;
};
UCLASS()
class MAZE_API AMazeGenerator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMazeGenerator();
	virtual void BuildMaze() {};
	virtual void LogMazeScheme() const;
	TArray<TArray<bool>> GetWalkableTerrain() const;
	virtual TArray <TArray<int8>> GetMazeScheme() const;
	void SetSeed(int32 Seed);
	virtual void SetCharacterMap(const TMap<int8, FMazeProperties>&);
	// Function to get valid starting coordinates for a character. Implemented differently in every MazeGenerator.
	virtual FIntPoint GetRandomCharacterStartingPoint() const { return FIntPoint(0, 0); };
protected:
	UPROPERTY(Category = AlgorithmProperties, EditAnywhere)
		uint64 WorldSeed;
	UPROPERTY(Category = AlgorithmProperties, EditAnywhere)
		bool bUseCustomSeed;
	UPROPERTY(Category = AlgorithmProperties, EditAnywhere)
		TMap<FName, int8> CharacterMap;
	FRandomStream RStream;
	TArray<TArray<int8>> MazeScheme;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
