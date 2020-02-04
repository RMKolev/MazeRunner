#include "../Public/Rectangle.h"

FRectangle::FRectangle(int32 X, int32 Y, int32 Width, int32 Height) : TopLeft(X, Y), Width(Width), Height(Height) {
}
FString FRectangle::ToString()
{
	return FString("Rectangle: TopLeft:(" + FString::FromInt(this->TopLeft.X) + "," + FString::FromInt(this->TopLeft.Y) 
		+ "), Width:"+ FString::FromInt(Width) + ", Height:" + FString::FromInt(Height)) ;
}
int FRectangle::Clamp(int V, int Lo, int Hi) {
	if (Lo > Hi) Swap<int>(Lo, Hi);
	return (V < Lo) ? Lo : (Hi < V) ? Hi : V;
}
FIntPoint FRectangle::GetBottomLeft() const {
	return FIntPoint(TopLeft.X + Width, TopLeft.Y + Height);
}
bool FRectangle::IntersectsWith(const FRectangle& R) const
{

	return !(TopLeft.X + Width <= R.TopLeft.X ||
		TopLeft.Y + Height <= R.TopLeft.Y ||
		TopLeft.X >= R.TopLeft.X + R.Width ||
		TopLeft.Y >= R.TopLeft.Y + R.Height);
}
FIntPoint FRectangle::GetNearestPointFrom(const FRectangle& R) const
{
	int NewXR2 = Clamp(TopLeft.X, R.TopLeft.X, R.TopLeft.X + R.Width - 1);
	int NewYR2 = Clamp(TopLeft.Y, R.TopLeft.Y, R.TopLeft.Y + R.Height - 1);
	return FIntPoint(NewXR2, NewYR2);
}

FIntPoint FRectangle::GetNearestPointTo(const FRectangle& r) const
{
	FIntPoint P = GetNearestPointFrom(r);

	int NewXR1 = Clamp(P.X, TopLeft.X, TopLeft.X + Width - 1);
	int NewYR1 = Clamp(P.Y, TopLeft.Y, TopLeft.Y + Height - 1);

	return FIntPoint(NewXR1, NewYR1);
}
uint64 FRectangle::GetDistanceSquaredTo(FRectangle R2) const
{
	return (GetNearestPointTo(R2) - GetNearestPointFrom(R2)).SizeSquared();
}
uint64 FRectangle::GetDistanceToCenterSquared() const
{
	return (int64_t)TopLeft.X * TopLeft.X + (int64_t)TopLeft.Y * TopLeft.Y;
}

bool FRectangle::operator<(const FRectangle R2) const {
	return GetDistanceToCenterSquared() < R2.GetDistanceToCenterSquared();
}
bool FRectangle::operator<=(const FRectangle R2) const {
	return GetDistanceToCenterSquared() <= R2.GetDistanceToCenterSquared();
}

bool FRectangle::ContainsPoint(const FIntPoint& P) const
{
	return P.X >= TopLeft.X && P.X <= TopLeft.X + Width - 1 &&
		P.Y >= TopLeft.Y && P.Y <= TopLeft.Y + Height - 1;
}
FRectangle FRectangle::GetIntersectionRectangle(const FRectangle& R) const {
	if (!IntersectsWith(R)) return FRectangle(0, 0, -1, -1);
	FIntPoint P1 = GetNearestPointFrom(R);
	FIntPoint R2Down = R.GetBottomLeft();
	if (ContainsPoint(R2Down)) {
		return FRectangle(P1.X, P1.Y, R2Down.X - P1.X, R2Down.Y - P1.Y);
	}
	return FRectangle(P1.X, P1.Y, TopLeft.X + Width - P1.X, TopLeft.Y + Height - P1.Y);
}
