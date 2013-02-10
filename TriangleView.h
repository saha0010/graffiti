#ifndef TRIANGLEVIEW
#define TRIANGLEVIEW

#include <vlgGLObserver.h>
#include "Triangle.h"

//! View Klasse für die Ausgabe von Triangle
class TriangleView : public vlgGLObserver
{
public:
	//!Default Konstruktor 
	TriangleView(void);

	//!Konstruktor
	/*!
	 *	\param std::vector<Triangle> &t // GraffitiEngine::triangleList
	 */
	TriangleView(std::vector<Triangle> &t);

private:
	
	//! Grafische Ausgabe, wird in der display()-Funktion der Anwedungsklasse aufgerufen
	/*!
		* Die draw-Funktion ist für das malen
		* der Dreiecke zuständig. Diese Funktion wird von der Anwednungsklasse konstant
		* automatisch aufgerufen, ohne das ein notify() notwendig ist.
	*/
	virtual void draw(void);

	//! Update, Änderungen werden angepasst
	virtual bool update(const vlgSubject &changedSubject);

	//! Das Subject, das wir beobachten
	std::vector<Triangle> &triangles;
};
#endif