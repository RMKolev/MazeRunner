#include "../Public/Rectangle.h"

FRectangle::FRectangle(int x, int y, int width, int height) : topLeft(x, y), width(width), height(height) {
}
int FRectangle::clamp(int v, int lo, int hi) {
	if (lo > hi) Swap<int>(lo, hi);
	return (v < lo) ? lo : (hi < v) ? hi : v;
}
FIntPoint FRectangle::getBottomLeft() const {
	return FIntPoint(topLeft.X + width, topLeft.Y + height);
}
bool FRectangle::intersectsWith(const FRectangle& r) const
{

	return !(topLeft.X + width <= r.topLeft.X ||
		topLeft.Y + height <= r.topLeft.Y ||
		topLeft.X >= r.topLeft.X + r.width ||
		topLeft.Y >= r.topLeft.Y + r.height);
}
FIntPoint FRectangle::getNearestPointFrom(const FRectangle& r) const
{
	int newXR2 = clamp(topLeft.X, r.topLeft.X, r.topLeft.X + r.width - 1);
	int newYR2 = clamp(topLeft.Y, r.topLeft.Y, r.topLeft.Y + r.height - 1);
	return FIntPoint(newXR2, newYR2);
}

FIntPoint FRectangle::getNearestPointTo(const FRectangle& r) const
{
	FIntPoint p = getNearestPointFrom(r);

	int newXR1 = clamp(p.X, topLeft.X, topLeft.X + width - 1);
	int newYR1 = clamp(p.Y, topLeft.Y, topLeft.Y + height - 1);

	return FIntPoint(newXR1, newYR1);
}
uint64 FRectangle::getDistanceSquaredTo(FRectangle r2) const
{
	return (getNearestPointTo(r2) - getNearestPointFrom(r2)).SizeSquared();
}
uint64 FRectangle::getDistanceToCenterSquared() const
{
	return (int64_t)topLeft.X * topLeft.X + (int64_t)topLeft.Y * topLeft.Y;
}

bool FRectangle::operator<(const FRectangle r2) const {
	return getDistanceToCenterSquared() < r2.getDistanceToCenterSquared();
}
bool FRectangle::operator<=(const FRectangle r2) const {
	return getDistanceToCenterSquared() <= r2.getDistanceToCenterSquared();
}

bool FRectangle::containsPoint(const FIntPoint& p1) const
{
	return p1.X >= topLeft.X && p1.X <= topLeft.X + width - 1 &&
		p1.Y >= topLeft.Y && p1.Y <= topLeft.Y + height - 1;
}
FRectangle FRectangle::getIntersectionRectangle(const FRectangle& r2) const {
	if (!intersectsWith(r2)) return FRectangle(0, 0, -1, -1);
	FIntPoint p1 = getNearestPointFrom(r2);
	FIntPoint r2Down = r2.getBottomLeft();
	if (containsPoint(r2Down)) {
		return FRectangle(p1.X, p1.Y, r2Down.X - p1.X, r2Down.Y - p1.Y);
	}
	return FRectangle(p1.X, p1.Y, topLeft.X + width - p1.X, topLeft.Y + height - p1.Y);
}
