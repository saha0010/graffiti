#include "Triangle.h"

Triangle::Triangle(float x, float y, float z, float s, int i):size(s)
{
	setX(x);
	setY(y);
	setZ(z);
	setFilled(true);
	setActiveColorByIndex(i);
}


Triangle::~Triangle(void)
{
}
void Triangle::setSize(float s){size=s;}
float Triangle::getSize(void){return (float)size;}