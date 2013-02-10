#ifndef RECTANGLE
#define RECTANGLE

#include "Shape.h"

//! Modell Klasse für ein Rechteck
/*!
 * Für diese Klasse existiert momentan keine View. Sie kann also nicht angezeigt werden!!
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

	//! Getter Mehtode für height
	float getHeight(void);

	//! Getter Methode für width
	float getWidth(void);

	//! Setter Methode für height
	void setHeight(float h);

	//! Setter Methode für width
	void setWidth(float w);

private:
	float width;	//!< Variable für die Weite des Recheckes
	float height;	//!< Variable für die Breite des Recheckes

};
#endif RECTANGLE