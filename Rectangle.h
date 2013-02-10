#ifndef RECTANGLE
#define RECTANGLE

#include "Shape.h"

//! Modell Klasse f�r ein Rechteck
/*!
 * F�r diese Klasse existiert momentan keine View. Sie kann also nicht angezeigt werden!!
 * Lediglich die Klasse Stamp erbt von dieser Klasse.
 */
class Rectangle : public Shape
{
public:
	//! Default Konstruktor
	Rectangle(void);

	//! Konstruktor
	/*!
	 *	\param float x, float y, float width, float height, bool fill
	 */
	Rectangle(float x, float y, float w=10.0f, float h=10.0f, bool fill=false);

	//! Dekonstruktor
	~Rectangle(void);

	//! Getter Mehtode f�r height
	float getHeight(void);

	//! Getter Methode f�r width
	float getWidth(void);

	//! Setter Methode f�r height
	void setHeight(float h);

	//! Setter Methode f�r width
	void setWidth(float w);

private:
	float width;	//!< Variable f�r die Weite des Recheckes
	float height;	//!< Variable f�r die Breite des Recheckes

};
#endif RECTANGLE