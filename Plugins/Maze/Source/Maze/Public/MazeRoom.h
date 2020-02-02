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
	UPROPERTY(EditAnywhere)
		FString roomName;
	UPROPERTY(Category = MapsAndSets, EditAnywhere)
		TArray<FMazeActorParameters> components;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Sets default values for this actor's properties
	AMazeRoom();
	//FIntPoint GetMazeCoordinates() const;
	FString GetName() const { return this->roomName; }
	auto GetMazeComponentIterator() const { return components.CreateConstIterator(); }
};
