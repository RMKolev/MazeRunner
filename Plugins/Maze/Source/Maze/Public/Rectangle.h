// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Rectangle.generated.h"
/**
 * 
 */
USTRUCT()
struct MAZE_API FMazePoint {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	int x;
	UPROPERTY(EditAnywhere)
	int y;

	FMazePoint(int x, int y) :x(x), y(y) {}
	FMazePoint() = default;
	static int getDistanceSquared(const FMazePoint p1, const FMazePoint p2) {
		return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
	}
	bool operator==(const FMazePoint& p) const {
		return x == p.x && y == p.y;
	}
	FMazePoint operator+(FMazePoint f1) {
		return FMazePoint(this->x + f1.x, this->y + f1.y);
	}
};
inline uint32 GetTypeHash(const FMazePoint& mp)
{
	return mp.x * 1001 + mp.y * 1003;
}

class MAZE_API FRectangle
{
private:
	FMazePoint topLeft;
	int width;
	int height;
public:
	static int clamp(int, int, int);
	FMazePoint getBottomLeft() const;
	bool intersectsWith(const FRectangle& r) const;
	FMazePoint getNearestPointFrom(const FRectangle& r) const;
	FMazePoint getNearestPointTo(const FRectangle& r) const;
	uint64 getDistanceSquaredTo(FRectangle r2) const;
	uint64 getDistanceToCenterSquared() const;
	bool operator<(const FRectangle r2) const;
	bool operator<=(const FRectangle r2) const;
	bool containsPoint(const FMazePoint&) const;
	FRectangle getIntersectionRectangle(const FRectangle&) const;
	FRectangle(int, int, int, int);
	FRectangle() = default;
	~FRectangle() = default;
};