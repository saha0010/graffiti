#ifndef STAMPVIEW
#define STAMPVIEW

#include "Stamp.h"
#include <vlgGLObserver.h>

//! View mit einer OpenGL-Ausgabe
class StampView : public vlgGLObserver
{
public:
	//!Default-Konstruktor zur Initialisierung
	StampView(void);
	//!Konstruktor mit einer Liste der angehängten Bitmaps
	StampView(std::vector<Stamp> &s);

private:
	//! Grafische Ausgabe, wird anstatt Display() aufgerufen
	/*!
		* Die draw-Funktion der StampView schaltet die 2D-Texturen frei und
		* bindet die aktuelle Bitmap-Textur an ein erstelltes Rechteck,
		* jenes vor bestimmte xOffSet- und yOffSet-Werte besitzt. Und an die
		* aktuelle Postion translatiert wird. Danach werden die 2D-Texturen 
		* wieder ausgeschaltet um kein Fehlverhalten mit glColor hervorzurufen.
	*/
	virtual void draw(void);

	//! Update, Änderungen werden angepasst
	virtual bool update(const vlgSubject &changedSubject);

	//! Das Subject, das wir beobachten
	std::vector<Stamp> &stamps;	
};
#endif