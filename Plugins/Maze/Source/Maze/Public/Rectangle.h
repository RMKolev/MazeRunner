// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
struct MAZE_API MazePoint {
	int x;
	int y;
	MazePoint(int x, int y) :x(x), y(y) {}

	static int getDistanceSquared(const MazePoint p1, const MazePoint p2) {
		return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
	}
	bool operator==(const MazePoint& p) const {
		return x == p.x && y == p.y;
	}
};

class MAZE_API FRectangle
{
private:
	MazePoint topLeft;
	int width;
	int height;
public:
	static int clamp(int, int, int);
	MazePoint getBottomLeft() const;
	bool intersectsWith(const FRectangle& r) const;
	MazePoint getNearestPointFrom(const FRectangle& r) const;
	MazePoint getNearestPointTo(const FRectangle& r) const;
	uint64 getDistanceSquaredTo(FRectangle r2) const;
	uint64 getDistanceToCenterSquared() const;
	bool operator<(const FRectangle r2) const;
	bool operator<=(const FRectangle r2) const;
	bool containsPoint(const MazePoint&) const;
	FRectangle getIntersectionRectangle(const FRectangle&) const;
	FRectangle(int, int, int, int);
	FRectangle() = default;
	~FRectangle() = default;
};