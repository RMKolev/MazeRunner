// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BlockBuilder.h"
#include "Engine/World.h"
#include "BlockBuilderWrapper.generated.h"

UCLASS()
class MAZE_API ABlockBuilderWrapper : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABlockBuilderWrapper();

	ABlockBuilder* SpawnBlockBuilderBP(FVector Location, FRotator Rotation, FActorSpawnParameters SpawnInfo);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(Category = MazeProperties, EditAnywhere)
	TSubclassOf<class ABlockBuilder> BlockBuilderClass;
};
