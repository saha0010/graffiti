#ifndef CIRCLELINEVIEW
#define CIRCLELINEVIEW

#include <vlgGLObserver.h>
#include <vlgShaderHandler.h>
#include <vlgShaderUniform.h>
#include <string>

#include "Line.h"


//! View mit einer OpenGL-Ausgabe
class CircleLineView : public vlgGLObserver
{

public:

	CircleLineView(std::vector<Line> &l);

	//! Grafische Ausgabe, wird in der display()-Funktion des Kerns aufgerufen
	/*!
		* Die draw-Funktion ist f�r das betrachten
		* der aktuell gemalten Linie zust�ndig. Er pr�ft welcher \a mode 
		* aktiv ist und zeichnet die Linie entsprechenden den erhaltenen
		* x und y Werten aus der myX- und myY-Liste und den aktiven
		* RGB-Anteilen der aktiven Farbe.
	*/
	virtual void draw(void);
    //! Initialisierung des GLSL Shader-Handlers
	/*!
	 * Setzt einen g�ltigen OpenGL-Kontext voraus; aufrufen in Anwendungsklasse::initContext() !!!!!
	 */
	void initShader(void);

	//! Update, �nderungen werden angepasst
	virtual bool update(const vlgSubject &changedSubject);

private:
	//! Zeiger auf Shader-Handler
	vlgShaderHandler *shader;
	//! Zeiger Uniform-Varibalen
	/*!
	 *	�bergibt die aktive Farbe an den Shader weiter.
	 */
	vlgShaderUniform *uniform;
	//! Methode um Uniform Variable zu setztn
	void setUniforms(Line l);

	//! Error-Code des Shader-Handlers
	short errorCode;
	//! Name des Vertex-Shaders
	std::string vertexShader;
	//! Zeiger auf das Subject, das wir beobachten
	std::vector<Line> &line;

	float zd;
	float zdO;
	float zE;
	float zTmp;
	
};
#endif 
