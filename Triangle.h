#ifndef TRIANGEL
#define TRIANGEL

#include "Shape.h"

class Triangle : public Shape
{
public:
	Triangle(float x, float y, float width, float height, int i);
	~Triangle(void);

	float getWidth(void);
	float getHeight(void);

private:
	float width;
	float height;
};
#endif 