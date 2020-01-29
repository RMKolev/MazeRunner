#include "../Public/Rectangle.h"

FRectangle::FRectangle(int x, int y, int width, int height) : topLeft(x, y), width(width), height(height) {
}
int FRectangle::clamp(int v, int lo, int hi) {
	if (lo > hi) Swap<int>(lo, hi);
	return (v < lo) ? lo : (hi < v) ? hi : v;
}
MazePoint FRectangle::getBottomLeft() const {
	return MazePoint(topLeft.x + width, topLeft.y + height);
}
bool FRectangle::intersectsWith(const FRectangle& r) const
{

	return !(topLeft.x + width <= r.topLeft.x ||
		topLeft.y + height <= r.topLeft.y ||
		topLeft.x >= r.topLeft.x + r.width ||
		topLeft.y >= r.topLeft.y + r.height);
}
MazePoint FRectangle::getNearestPointFrom(const FRectangle& r) const
{
	int newXR2 = clamp(topLeft.x, r.topLeft.x, r.topLeft.x + r.width - 1);
	int newYR2 = clamp(topLeft.y, r.topLeft.y, r.topLeft.y + r.height - 1);
	return MazePoint(newXR2, newYR2);
}

MazePoint FRectangle::getNearestPointTo(const FRectangle& r) const
{
	MazePoint p = getNearestPointFrom(r);

	int newXR1 = clamp(p.x, topLeft.x, topLeft.x + width - 1);
	int newYR1 = clamp(p.y, topLeft.y, topLeft.y + height - 1);

	return MazePoint(newXR1, newYR1);
}
uint64 FRectangle::getDistanceSquaredTo(FRectangle r2) const
{
	return MazePoint::getDistanceSquared(getNearestPointTo(r2), getNearestPointFrom(r2));
}
uint64 FRectangle::getDistanceToCenterSquared() const
{
	return (int64_t)topLeft.x * topLeft.x + (int64_t)topLeft.y * topLeft.y;
}

bool FRectangle::operator<(const FRectangle r2) const {
	return getDistanceToCenterSquared() < r2.getDistanceToCenterSquared();
}
bool FRectangle::operator<=(const FRectangle r2) const {
	return getDistanceToCenterSquared() <= r2.getDistanceToCenterSquared();
}

bool FRectangle::containsPoint(const MazePoint& p1) const
{
	return p1.x >= topLeft.x && p1.x <= topLeft.x + width - 1 &&
		p1.y >= topLeft.y && p1.y <= topLeft.y + height - 1;
}
FRectangle FRectangle::getIntersectionRectangle(const FRectangle& r2) const {
	if (!intersectsWith(r2)) return FRectangle(0, 0, -1, -1);
	MazePoint p1 = getNearestPointFrom(r2);
	MazePoint r2Down = r2.getBottomLeft();
	if (containsPoint(r2Down)) {
		return FRectangle(p1.x, p1.y, r2Down.x - p1.x, r2Down.y - p1.y);
	}
	return FRectangle(p1.x, p1.y, topLeft.x + width - p1.x, topLeft.y + height - p1.y);
}
