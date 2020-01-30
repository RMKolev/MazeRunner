// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BlockBuilder.generated.h"

UCLASS()
class MAZE_API ABlockBuilder : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABlockBuilder();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	float XPosition;
	float CurrTime;

	UPROPERTY()
	FVector PrevPosition;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AMazeActor> WallActorClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AMazeActor> FloorActorClass;

};
