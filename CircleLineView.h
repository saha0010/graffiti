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
	//! Konstruktor
	/*!
	 * \param std::vector<Line> &l //Eine Liste aus Lines; GraffitiEngine::lineList
	*/
	CircleLineView(std::vector<Line> &l);

	//! Grafische Ausgabe, wird in der display()-Funktion der Anwedungsklasse aufgerufen
	/*!
		* Die draw-Funktion ist f�r das malen
		* der Linien zust�ndig. Diese Funktion wird von der Anwednungsklasse konstant
		* automatisch aufgerufen, ohne das ein notify() notwendig ist.
	*/
	virtual void draw(void);

    //! Initialisierung des GLSL Shader-Handlers
	/*!
	 * Setzt einen g�ltigen OpenGL-Kontext voraus; aufrufen in Anwendungsklasse::initContext()!!!!!
	 */
	void initShader(void);

	//! Update, �nderungen werden angepasst
	virtual bool update(const vlgSubject &changedSubject);

	//! Setter Methode f�r Membervariable "blending"
	void setBlending(bool b);

	//! Getter Methode f�r Membervariable "blendind"
	bool getBlending(void);

private:
	//! Zeiger auf Shader-Handler
	vlgShaderHandler *shader;

	//! Zeiger Uniform-Varibalen
	/*!
	 *	�bergibt die aktive Farbe an den Shader weiter.
	 */
	vlgShaderUniform *uniform;

	//! Methode um Uniform Variable zu setzen
	void setUniforms(Line l);

	//! Error-Code des Shader-Handlers
	short errorCode;

	//! Name des Vertex-Shaders
	std::string vertexShader;

	//! Referenz des Subjects, das wir beobachten
	std::vector<Line> &line;

	//! Varibale um Blending an oder aus zuschalten
	bool blending;

	float zE; //!< Varibale zum setzen der Z-Ebenen Position des Objekts
	
};
#endif 
