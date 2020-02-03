// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//#include "Rectangle.generated.h"
/**
 * 
 */

/*USTRUCT()
struct MAZE_API FIntPoint {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	int x;
	UPROPERTY(EditAnywhere)
	int y;

	FIntPoint(int x, int y) :x(x), y(y) {}
	FIntPoint() = default;
	static int getDistanceSquared(const FIntPoint p1, const FIntPoint p2) {
		return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
	}
	bool operator==(const FIntPoint& p) const {
		return x == p.x && y == p.y;
	}
	FIntPoint operator+(FIntPoint f1) {
		return FIntPoint(this->x + f1.x, this->y + f1.y);
	}
};*/
class MAZE_API FRectangle
{
private:
	FIntPoint topLeft;
	int width;
	int height;
public:
	static int clamp(int, int, int);
	FIntPoint getBottomLeft() const;
	bool intersectsWith(const FRectangle& r) const;
	FIntPoint getNearestPointFrom(const FRectangle& r) const;
	FIntPoint getNearestPointTo(const FRectangle& r) const;
	uint64 getDistanceSquaredTo(FRectangle r2) const;
	uint64 getDistanceToCenterSquared() const;
	bool operator<(const FRectangle r2) const;
	bool operator<=(const FRectangle r2) const;
	bool containsPoint(const FIntPoint&) const;
	FRectangle getIntersectionRectangle(const FRectangle&) const;
	FRectangle(int, int, int, int);
	FRectangle() = default;
	~FRectangle() = default;
};