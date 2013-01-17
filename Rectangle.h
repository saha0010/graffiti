#ifndef RECTANGLE
#define RECTANGLE

#include "Shape.h"

class Rectangle : public Shape
{
public:
	Rectangle(void);
	Rectangle(float x, float y, float w=10.0f, float h=10.0f, bool fill=false);
	~Rectangle(void);

	float getHeight(void);
	float getWidth(void);

	void setHeight(float h);
	void setWidth(float w);

private:
	float width;
	float height;

};
#endif RECTANGLE