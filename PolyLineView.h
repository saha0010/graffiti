#ifndef POLYLINEVIEW
#define POLYLINEVIEW

#include <vlgGLObserver.h>
#include "PolyLine.h"
#include "vector"

//! View mit einer OpenGL-Ausgabe
class PolyLineView : public vlgGLObserver
{

public:
	//! Konstruktor mit einer Referenz des Subject, das wir beobachten
	PolyLineView(std::vector<Line> &l);

	//! Grafische Ausgabe, wird anstatt Display() aufgerufen
	/*!
		* Die draw-Funktion der PolyLineView ist für das betrachten
		* aller Linie in der Linienliste zuständig. Er prüft welcher \a mode 
		* bei der jeweiligen Linie aktiv ist und zeichnet die Linie entsprechenden
		* den erhaltenen x und y Werten aus der myX- und myY-Liste und den aktiven
		* RGB-Anteilen der aktiven Farbe der jeweiligen Linie in der Liste nach.
	*/
	virtual void draw(void);

	//! Update, Änderungen werden angepasst
	virtual bool update(const vlgSubject &changedSubject);

private:
	//! Das Subject, das wir beobachten
	std::vector<Line> &line;	

	float zd;
	float zdO;
	float zE;
	float zTmp;
};
#endif
