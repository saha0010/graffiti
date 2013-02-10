#ifndef STAMPVIEW
#define STAMPVIEW

#include "Stamp.h"
#include <vlgGLObserver.h>

//! View Klasse für die Ausgabe von Stamp
class StampView : public vlgGLObserver
{
public:
	//!Default Konstruktor
	StampView(void);
	//!Konstruktor
	/*!
	 * \param std::vector<Stamp> &s // GraffitiEngine::stampList
	 */
	StampView(std::vector<Stamp> &s);

private:
	//! Grafische Ausgabe, wird anstatt Display() aufgerufen
	/*!
		* Die draw-Funktion der StampView schaltet die 2D-Texturen frei und
		* bindet die aktuelle Bitmap-Textur an ein erstelltes Rechteck,
		* jenes bestimmte xOffSet- und yOffSet-Werte besitzt. Diese werden an die
		* aktuelle Postion translatiert. Danach werden die 2D-Texturen 
		* wieder ausgeschaltet um kein Fehlverhalten mit glColor hervorzurufen.
	*/
	virtual void draw(void);

	//! Update, Änderungen werden angepasst
	virtual bool update(const vlgSubject &changedSubject);

	//! Das Subject, das wir beobachten
	std::vector<Stamp> &stamps;	
};
#endif