#pragma once
class Point
{
private:
	float x, y;
public:
	Point(float x, float y);
	float getX();
	float getY();
};


class PointList
{
public:
	PointList(int pointCount);
	void add(Point point);

private:
	
	float pointList[];
};