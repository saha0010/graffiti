#ifndef CIRCLE
#define CIRCLE

#include <vlgSubject.h>
#include <vector>
#include <iostream>
#include "Shape.h"

//! Modell Klasse f�r Kreise
class Circle : public Shape
{
public:
	//! Konstruktor
	/*
	 * \param float radius, float x, float y, float z, int farbindex
	 */
	Circle(float radius, float x, float y, float z, int farbIndex);

	//! Setter Methode f�r radius
	void setRadius(float r);

	//! Getter Methode f�r radius
	float getRadius(void);

private:
	float radius;	//!<  Varibale f�r Radius des Kreises
};
#endif