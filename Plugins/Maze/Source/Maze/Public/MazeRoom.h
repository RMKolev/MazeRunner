// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MazeRoom.generated.h"
USTRUCT()
struct FMazeActorParameters {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FString Name;
	UPROPERTY(EditAnywhere)
	FIntVector Scale;
	UPROPERTY(EditAnywhere)
	FIntPoint LocalCoordinates;
	UPROPERTY(EditAnywhere)
		bool bScale = true;
	FMazeActorParameters(const FString& Name, const FIntVector& Scale, const FIntPoint& LocalCoordinates, bool bScale = true) :
		Name(Name), Scale(Scale), LocalCoordinates(LocalCoordinates), bScale(bScale) {};
	FMazeActorParameters() = default;
};
UCLASS()
class MAZE_API AMazeRoom : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(Category = MazeParameters, EditAnywhere)
		FString RoomName; // Name of the room
	UPROPERTY(Category = MazeParameters, EditAnywhere)
		TArray<FMazeActorParameters> Components; //Components of the room
	UPROPERTY(Category = MazeParameters, EditAnywhere)
		bool bGenerateWalls;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	//virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Sets default values for this actor's properties
	AMazeRoom();
	//AMazeRoom(const FString&, const TArray<FMazeActorParameters>&, const TArray<FIntPoint>& ExitPoints);
	FString GetMazeRoomName() const { return this->RoomName; }
	auto GetMazeComponentIterator() const { return Components.CreateConstIterator(); }
	virtual void GenerateWalls(const FIntPoint& RoomSize, const TArray<FIntPoint>& ExitPoints);
};
