#ifndef TRIANGLEVIEW
#define TRIANGLEVIEW

#include <vlgGLObserver.h>
#include "Triangle.h"

//! View mit einer OpenGL-Ausgabe
class TriangleView : public vlgGLObserver
{
public:
	//!Default-Konstruktor zur Initialisierung
	TriangleView(void);
	//!Konstruktor mit einer Liste der erstellen Kreise
	TriangleView(std::vector<Triangle> &t);

private:
	virtual void draw(void);

	//! Update, Änderungen werden angepasst
	virtual bool update(const vlgSubject &changedSubject);

	//! Das Subject, das wir beobachten
	std::vector<Triangle> &triangles;
};
#endif