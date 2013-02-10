#include "Triangle.h"

Triangle::Triangle(float x, float y, float z, float size, int farbindex):size(size)
{
	setX(x);
	setY(y);
	setZ(z);
	setFilled(true);
	setActiveColorByIndex(farbindex);
}

Triangle::~Triangle(void)
{
}
void Triangle::setSize(float s)
{size=s;}

float Triangle::getSize(void)
{return (float)size;}