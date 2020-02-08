// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "MazeBuilderWrapper.generated.h"

class AMazeBuilder;

UCLASS()
class MAZE_API AMazeBuilderWrapper : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMazeBuilderWrapper();

	void InstantiateMazeBuilder();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(Category = MazeProperties, EditAnywhere)
		TSubclassOf<class AMazeBuilder> MazeBuilderClass;

	UPROPERTY(Category = MazeProperties, VisibleAnywhere)
		FVector CharacterLocation;

	UPROPERTY(Category = MazeProperties, VisibleAnywhere)
		FString CharacterName;

	UPROPERTY(Category = MazeProperties, VisibleAnywhere)
		bool bSpawnCharacter;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
