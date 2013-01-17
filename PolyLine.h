#ifndef POLYLINE
#define POLYLINE

#include <iostream>
#include "vector"
#include "Line.h"

//! Subjekt mit x und y Werten, Farben und Modiauswahl
class PolyLine : public Line
{
public:
	//!Default-Konstruktor
	PolyLine(void);
	//! Konstruktor zum setzen der Farbe
	PolyLine(int i);



	//! Funktion zum ändern der Darstellung der aktuellen Linie
	/*!
		* Die aktuelle Linie wird mit unterschiedlich dargestellt, in
		* Abhängigkeit des aktiven \a mode Wertes. Hier wird der mode
		* durchgeschaltet.
		*
		* mode = 0 entspricht GL_Line_Strip, 
		* mode = 1 entspricht GL_Line_Loop,
		* mode = 2 entspricht GL_Polygon.
	*/
	void changePolyLineMode(void);
	
	int getMode(void);
private:
	int mode;	//!< Variable zum ändern der Darstellung - GL_Line_Strip, GL_Line_Loop, GL_Polygon

};
#endif
