// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Maze.h"
#include "MazeBuilder.h"
#include "MazeGenerator.generated.h"

UCLASS()
class MAZE_API AMazeGenerator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMazeGenerator();
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void BuildMaze() {};
	virtual void LogMazeScheme() const;
	TArray<TArray<bool>> GetWalkableTerrain() const;
	virtual TArray <TArray<int8>> GetMazeScheme() const;
	void SetSeed(int32 Seed);
	virtual void SetCharacterMap(const TMap<int8, FMazeProperties>&);
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
