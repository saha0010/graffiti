#ifndef TRIANGLE
#define TRIANGLE

#include <vlgSubject.h>
#include <vector>
#include <iostream>
#include "Shape.h"

//! Modell Klasse für Dreiecke
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

	//! Setter Methode für size
	void setSize(float s);

	//! Getter Methode für size
	float getSize(void);

private:
	
	float size;	//!< Variable um später die Größe des Dreieckes beeinflussen zu können
				/*!<
				 *	Diese Funktion wurde noch nicht implementiert!!!
				 */
};
#endif