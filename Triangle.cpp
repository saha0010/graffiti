#include "Triangle.h"

Triangle::Triangle(float x, float y, float width, float height, int i):width(width),height(height)
{
	setX(x);
	setY(y);
	setFilled(true);
	setActiveColorByIndex(i);
}


Triangle::~Triangle(void)
{
}

float Triangle::getWidth()
{return width;}
float Triangle::getHeight()
{return height;}