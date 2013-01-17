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
	//!Konstruktor mit einer Liste der erstellen Kreise
	CircleView(std::vector<Circle> &c);

private:
	float h;	//!< 2 * Pi : Anzahl der Ecken, dient zum bestimmen der Punkte entlang der Kreis gezeichnet wird --> Source Prof.Brill Computergrafik Beispiel "TrafficLight"	
	int n;		//!< Anzahl der Ecken für die Darstellung des Kreises

	//! Grafische Ausgabe, wird anstatt Display() aufgerufen
	/*!
		* Die draw-Funktion der CircleView ist für das betrachten
		* aller Kreise in der Kreiseliste zuständig. Er zeichnet 
		* den Kreis entsprechend den erhaltenen \a myCX und \a myCY Werten
		* und den aktiven RGB-Anteilen der aktiven Farbe des jeweiligen
		* Kreises in der Liste nach.
	*/
	virtual void draw(void);

	//! Update, Änderungen werden angepasst
	virtual bool update(const vlgSubject &changedSubject);

	//! Das Subject, das wir beobachten
	std::vector<Circle> &circles;
};
#endif