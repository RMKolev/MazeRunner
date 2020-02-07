// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BlockBuilder.h"
#include "Engine/World.h"
#include "MazeBuilderWrapper.generated.h"

UCLASS()
class MAZE_API AMazeBuilderWrapper : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMazeBuilderWrapper();

	void InstantiateMazeBuilder();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(Category = MazeProperties, EditAnywhere)
	TSubclassOf<class AMazeBuilder> MazeBuilderClass;
};
