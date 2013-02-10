#ifndef POLYLINEVIEW
#define POLYLINEVIEW

#include <vlgGLObserver.h>
#include "Line.h"
#include <vector>

//! View Klasse f�r die Ausgabe von Line
class PolyLineView : public vlgGLObserver
{
public:
	//! Konstruktor
	/*!
	 * \param std::vector<Line> &l //GraffitiEngine::lineList
	 */
	PolyLineView(std::vector<Line> &l);

	//! Grafische Ausgabe, wird in der display()-Funktion der Anwedungsklasse aufgerufen
	/*!
		* Die draw-Funktion ist f�r das malen
		* der Linien zust�ndig. Diese Funktion wird von der Anwednungsklasse konstant
		* automatisch aufgerufen, ohne das ein notify() notwendig ist.
	*/
	virtual void draw(void);

	//! Update, �nderungen werden angepasst
	virtual bool update(const vlgSubject &changedSubject);

private:
	
	std::vector<Line> &line; //!< Das Subject, das wir beobachten	
	float zE;  //!< Varibale zum setzen der Z-Ebenen Position des Objekts

};
#endif
