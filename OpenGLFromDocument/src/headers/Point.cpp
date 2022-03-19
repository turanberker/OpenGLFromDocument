#include "Point.h"
#include <iostream>

Point::Point(float x, float y) {
	this->x = x;
	this->y = y;
}

PointList::PointList(int pointCount) {
	this->pointList[pointCount * 3];
}

void PointList::add(Point point) {
	
}