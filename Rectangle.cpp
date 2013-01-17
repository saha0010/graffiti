#include "Rectangle.h"

Rectangle::Rectangle(void)
{}

Rectangle::Rectangle(float x, float y, 
					 float w, float h, bool fill):
					 width(w), height(h)
{
	setX(x);
	setY(y);
	setFilled(fill);
}

Rectangle::~Rectangle(void)
{
}

float Rectangle::getHeight(void)
{return height;}

float Rectangle::getWidth(void)
{return width;}
void Rectangle::setHeight(float h)
{height = h;}
void Rectangle::setWidth(float w)
{width = w;}