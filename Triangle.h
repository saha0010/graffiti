#ifndef TRIANGLE
#define TRIANGLE

#include <vlgSubject.h>
#include <vector>
#include <iostream>
#include "Shape.h"

//! Modell Klasse f�r Dreiecke
class Triangle : public Shape
{
public:
	//! Konstruktor
	/*!
	 *	\param float x, float y, float z, float size, int farbindex
	 */
	Triangle(float x, float y, float z,float size, int farbindex);

	//! Dekonstruktor
	~Triangle(void);

	//! Setter Methode f�r size
	void setSize(float s);

	//! Getter Methode f�r size
	float getSize(void);

private:
	
	float size;	//!< Variable um sp�ter die Gr��e des Dreieckes beeinflussen zu k�nnen
				/*!<
				 *	Diese Funktion wurde noch nicht implementiert!!!
				 */
};
#endif