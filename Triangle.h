#ifndef TRIANGLE
#define TRIANGLE

#include <vlgSubject.h>
#include <vector>
#include <iostream>
#include "Shape.h"

//! Klasse zum erstellen der Kreise
class Triangle : public Shape
{
public:
	//! Konstruktor mit Positionswerten(x,y,z) Größe (s) und dem Farbindex(i)
	Triangle(float x, float y, float z,float s, int i);
	~Triangle(void);
	void setSize(float s);
	float getSize(void);

private:
	
	float size;
};
#endif