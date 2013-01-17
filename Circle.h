#ifndef CIRCLE
#define CIRCLE

#include <vlgSubject.h>
#include <vector>
#include <iostream>
#include "Shape.h"

//! Klasse zum erstellen der Kreise
class Circle : public Shape
{
public:
	//! Konstruktor mit Positionswerten, Radius und Farbindex
	Circle(float radius, float x, float y, float z, int i);


	//! set-Funktion zum setzen des Radius
	void setRadius(float r);

	//! get-Funktion Radius
	float getRadius(void);



private:
	
	float radius;	//!< Varialbe - Radius	
};
#endif