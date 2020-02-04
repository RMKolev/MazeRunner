// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class MAZE_API FRectangle
{
private:
	FIntPoint TopLeft;
	int Width;
	int Height;
public:
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
	FRectangle(int, int, int, int);
	FRectangle() = default;
	~FRectangle() = default;
};