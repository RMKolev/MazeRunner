// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class MAZE_API FRectangle
{
private:
	FIntPoint TopLeft;
	int32 Width;
	int32 Height;
public:
	FIntPoint GetTopLeft() const { return TopLeft; }
	int32 GetWidth() const { return Width; }
	int32 GetHeight() const { return Height; }
	static int Clamp(int, int, int);
	FIntPoint GetBottomLeft() const;
	bool IntersectsWith(const FRectangle&) const;
	FIntPoint GetNearestPointFrom(const FRectangle&) const;
	FIntPoint GetNearestPointTo(const FRectangle&) const;
	uint64 GetDistanceSquaredTo(FRectangle) const;
	uint64 GetDistanceToCenterSquared() const;
	bool operator<(const FRectangle) const;
	bool operator<=(const FRectangle) const;
	bool ContainsPoint(const FIntPoint&) const;
	FRectangle GetIntersectionRectangle(const FRectangle&) const;
	FRectangle(int32 X, int32 Y, int32 Width, int32 Height);
	FRectangle() = default;
	~FRectangle() = default;
	FString ToString();
};