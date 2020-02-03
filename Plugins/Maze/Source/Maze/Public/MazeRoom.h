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
};
UCLASS()
class MAZE_API AMazeRoom : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(Category = MazeParameters, EditAnywhere)
		FString roomName; // Name of the room
	UPROPERTY(Category = MazeParameters, EditAnywhere)
		TArray<FMazeActorParameters> components; //Components of the room
	UPROPERTY(Category = MazeParameters, EditAnywhere)
		TArray<FIntPoint> exitPoints; // All points used as exits. It is essential they are entrances to the room, otherwise it will become impossible to enter it.

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Sets default values for this actor's properties
	AMazeRoom();
	//FIntPoint GetMazeCoordinates() const;
	FString GetMazeRoomName() const { return this->roomName; }
	auto GetMazeComponentIterator() const { return components.CreateConstIterator(); }
	auto GetExitPointsIterator() const { return exitPoints.CreateConstIterator(); }
};
