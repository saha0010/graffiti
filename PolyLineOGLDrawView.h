#ifndef POLYLINEOGLDRAWVIEW
#define POLYLINEOGLDRAWVIEW

#include <vlgGLObserver.h>
#include "Line.h"

//! View mit einer OpenGL-Ausgabe
class PolyLineOGLDrawView : public vlgGLObserver
{

public:
	//!Konstruktor mit einem Zeiger auf das Subject, das wir beobachten. Wird Haupts�chlich benutzt
	//PolyLineOGLDrawView(PolyLine *l);
	

	PolyLineOGLDrawView(std::vector<Line> &l);

	//! Grafische Ausgabe, wird anstatt Display() aufgerufen
	/*!
		* Die draw-Funktion der PolyLineOGLDrawView ist f�r das betrachten
		* der aktuell gemalten Linie zust�ndig. Er pr�ft welcher \a mode 
		* aktiv ist und zeichnet die Linie entsprechenden den erhaltenen
		* x und y Werten aus der myX- und myY-Liste und den aktiven
		* RGB-Anteilen der aktiven Farbe.
	*/
	virtual void draw(void);

	//! Update, �nderungen werden angepasst
	virtual bool update(const vlgSubject &changedSubject);

private:
	//! Zeiger auf das Subject, das wir beobachten
	std::vector<Line> &line;

	float zd;
	float zdO;
	float zE;
	float zTmp;
	
};
#endif 
