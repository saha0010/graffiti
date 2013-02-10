#include "Circle.h"

Circle::Circle(float r, float x, float y, float z, int farbIndex):radius(r)
{
	setX(x);
	setY(y);
	setZ(z);
	setFilled(true);
	setActiveColorByIndex(farbIndex);
}
	
	void Circle::setRadius(float r)
	{radius = r;}

	
	float Circle::getRadius(void)
	{return radius;}

