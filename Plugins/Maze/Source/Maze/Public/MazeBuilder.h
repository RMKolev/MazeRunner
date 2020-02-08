// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MazeGenerator.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "MazeBuilder.generated.h"

USTRUCT()
struct FMazeActor
{
	GENERATED_BODY();
	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> Asset;
	UPROPERTY(EditAnywhere)
		int8 Priority;
	UPROPERTY(EditAnywhere)
		int32 Quantity;
	UPROPERTY(EditAnywhere)
		FVector Offset;
	UPROPERTY(EditAnywhere)
		FVector Scale;
	UPROPERTY(EditAnywhere)
		bool bIsSafe;

};
USTRUCT()
struct FMazeBasis
{
	GENERATED_BODY()
		//The position of 0,0 
		UPROPERTY(EditAnywhere)
		FVector Start;
		//Assumes 1 = 100cm in Unreal Units
	UPROPERTY(EditAnywhere)
		FVector Scale;
	FMazeBasis(FVector Start, FVector Scale) : Start(Start)
	{
		if (Scale.X > 0 && Scale.Y > 0 && Scale.Z > 0) this->Scale = Scale;
	}
	FMazeBasis() :FMazeBasis(FVector(0, 0, 0), FVector(100, 100, 100)) {};
	FVector GetMazePointLocation(FIntPoint Mp) const
	{
		return Start + (FVector(Mp.X + 0.5, Mp.Y + 0.5, 0) *Scale*100);
	}
	FVector GetMazeComponentLocation(FIntPoint Mp, const FIntVector ComponentScale) const
	{
		return GetMazePointLocation(Mp) + FVector(ComponentScale.X, ComponentScale.Y, ComponentScale.Z) * (Scale*50);
	}
	FVector GetMazeActorLocation(FIntPoint Mp, const FIntVector ComponentScale) const
	{
		return GetMazeComponentLocation(Mp,ComponentScale) + FVector(0,0,1)*Scale*50;
	}
	
};

UCLASS()
class MAZE_API AMazeBuilder : public AActor
{
	GENERATED_BODY()
public:
	// Function to build the maze. To be implemented in heirs of class.
	virtual void BuildMaze() {};
	// Function to Generate The Maze via the MazeGenerator algorithms.
	// Sets the starting player location,MazeScheme, and WalkableTerrain.
	virtual void GenerateMaze();
	// Function that will place the actors from ActorsToPlace array, with priority = ascending ( 0 goes first)
	virtual void PlaceActors();
	void RegisterInstanceMeshComponents();
	void SetCharacterMap() {};
	bool GetBuildOnPlay() { return bBuildOnPlay; }
	bool GetGenerateOnPlay() { return bGenerateOnPlay; }
	FString GetCharacterName() { return CharacterName.ToString(); }
	FVector GetCharacterStartingLocation() { return Basis.GetMazeActorLocation(CharacterStartPoint, FIntVector(1, 1, 1)); }
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	// Sets default values for this actor's properties
	AMazeBuilder();
	FIntPoint GetRandomWalkablePoint(FRandomStream&);
protected:
	//A map for names when using a Character Matrix. 
	//Associates every value with a Name of an InstanceMesh which then adds the component
	UPROPERTY(Category = MazeAlgorithm, EditAnywhere)
		TSubclassOf<AMazeGenerator> MazeGenerator;
	UPROPERTY(EditAnywhere)
		TMap<int8, FMazeProperties> CharacterMap;
	//All the Instance Meshes to be initialised. Each actor here will receive an instance stored in InstanceMeshes
	UPROPERTY(EditAnywhere)
		TMap<FName, TSubclassOf<UInstancedStaticMeshComponent>> Assets;
	//Stores the InstancedStaticMeshComponents for quick retrieval
	UPROPERTY()
		TMap<FName, UInstancedStaticMeshComponent*> InstanceMeshes;
	// Basis for the built Maze. Used for calculating the positions of all maze points (and actors)
	UPROPERTY(EditAnywhere)
		FMazeBasis Basis;
	// Boolean value telling the builder whether to build the maze at runtime.
	UPROPERTY(Category = AlgorithmProperties, EditAnywhere)
		bool bBuildOnPlay;
	// Boolean value telling the builder whether to render the maze at runtime.
	UPROPERTY(Category = AlgorithmProperties, EditAnywhere)
		bool bGenerateOnPlay;
	UPROPERTY(Category = AlgorithmProperties, EditAnywhere)
		FName CharacterName;
	UPROPERTY(Category = AlgorithmProperties, EditAnywhere)
		TArray<FMazeActor> ActorsToPlace;
	FIntPoint CharacterStartPoint;
	// A matrix to store the Maze Schematic upon generation
	TArray<TArray<int8>> MazeScheme;
	TArray<TArray<bool>> WalkableTerrain;
	virtual void BeginPlay() override;
	int32 WorldSeed;

};