#ifndef CIRCLE
#define CIRCLE

#include <vlgSubject.h>
#include <vector>
#include <iostream>
#include "Shape.h"

//! Modell Klasse für Kreise
class Circle : public Shape
{
public:
	//! Konstruktor
	/*
	 * \param float radius, float x, float y, float z, int farbindex
	 */
	Circle(float radius, float x, float y, float z, int farbIndex);

	//! Setter Methode für radius
	void setRadius(float r);

	//! Getter Methode für radius
	float getRadius(void);

private:
	float radius;	//!<  Varibale für Radius des Kreises
};
#endif