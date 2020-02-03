// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MazeActor.h"
//#include "Rectangle.h"
#include "MazeRoom.generated.h"
USTRUCT()
struct FMazeActorParameters {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FString name;
	UPROPERTY(EditAnywhere)
	FIntVector scale;
	UPROPERTY(EditAnywhere)
	FIntPoint localCoordinates;
	UPROPERTY(EditAnywhere)
		bool bScale = true;
	FMazeActorParameters(const FString& name, const FIntVector& scale, const FIntPoint& localCoordinates, bool bScale = true) :
		name(name), scale(scale), localCoordinates(localCoordinates), bScale(bScale) {};
	FMazeActorParameters() = default;
};
UCLASS()
class MAZE_API AMazeRoom : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(Category = MazeParameters, EditAnywhere)
		FString roomName; // Name of the room
	UPROPERTY(Category = MazeParameters, EditAnywhere)
		TArray<FMazeActorParameters> components; //Components of the room
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
	//AMazeRoom(const FString&, const TArray<FMazeActorParameters>&, const TArray<FIntPoint>& exitPoints);
	FString GetMazeRoomName() const { return this->roomName; }
	auto GetMazeComponentIterator() const { return components.CreateConstIterator(); }
	virtual void GenerateWalls(const FIntPoint& roomSize, const TArray<FIntPoint>& exitPoints);
};
