// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Rectangle.h"
#include "GameFramework/Actor.h"
#include "MazeRoomGenerator.generated.h"

UCLASS()
class MAZE_API AMazeRoomGenerator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMazeRoomGenerator();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(Category=AlgorithmProperties,EditAnywhere)
		uint64 WorldSeed;
	UPROPERTY(Category = AlgorithmProperties, EditAnywhere)
		int32 NumberOfRooms;
	UPROPERTY(Category = AlgorithmProperties, EditAnywhere)
		FIntPoint MinimalRoomScale;
	UPROPERTY(Category = AlgorithmProperties, EditAnywhere)
		FIntPoint MaximumRoomScale;
public:
	TArray<FRectangle> GenerateMazeRooms();
	FRectangle GetRandomRectangle();
	auto getApproximateMinimalSpanTreeGraph(TArray<FRectangle>& rectangles, int32 neighborLimit = 80);
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;
};
