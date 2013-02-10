#ifndef CIRCLEVIEW
#define CIRCLEVIEW

#include <vlgGLObserver.h>
#include "Circle.h"

//! View mit einer OpenGL-Ausgabe
class CircleView : public vlgGLObserver
{
public:
	//!Default-Konstruktor zur Initialisierung
	CircleView(void);

	//!Konstruktor
	/*!
	 *	\param std::vector<Circle> &c // GraffitiEngine::circleList
	 */
	CircleView(std::vector<Circle> &c);

private:
	/*
	 * Source Prof.Brill Computergrafik Beispiel "TrafficLight"	
	 */
	float h;	//!< 2*Pi: Anzahl der Ecken, dient zum bestimmen der Punkte entlang der Kreis gezeichnet wird.	
	int n;		//!< Anzahl der Ecken für die Darstellung des Kreises

	//! Grafische Ausgabe, wird anstatt Display() aufgerufen
	/*!
		* Die draw-Funktion der CircleView ist für das betrachten
		* aller Kreise in der Kreiseliste zuständig.
	*/
	virtual void draw(void);

	//! Update, Änderungen werden angepasst
	virtual bool update(const vlgSubject &changedSubject);

	//! Das Subject, das wir beobachten
	std::vector<Circle> &circles;
};
#endif