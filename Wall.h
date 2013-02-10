#ifndef WALL
#define WALL

#include <vector>
#include <string>
#include <iostream>
#include "vlgTextureMap2D.h"
#include "Color.h"

//! Modell Klasse für den Hintergrund und das Interface
class Wall : public Color
{
public:
	//! Default-Konstruktor zur Initialisierung
	Wall(void);

	//! OpenGL Initialisierung
	/*!
		* Die init-Funktion schaltet die 2D-Texturen frei und
		* lädt die Bitmaps als Texturen ein. Danach werden die 
		* 2D-Texturen wieder ausgeschaltet um kein Fehlverhalten
		* mit glColor hervorzurufen.
	*/
	void init(void);
	
	
	int backgroundIndex;	//!< Variable des aktuellen Hintergrundwertes
	
	bool received;			//!< Variable - Boolean ob Tracker-Daten empfangen werden
	bool showDataReceived;	//!< Variable - Boolean soll visuelle Tracker-Daten Rückgabe ein/ausgeblendet sein
	
	GLuint texNames[5];		//!< Array zum Halten der Texturen
	
	vector<vlgTextureMap2D> textureMaps;	//!< Liste für zweidimensionale Texturen
	
	vector<string> textureNames;	//!< Liste der Texturnamen
	
	vlgTextureMap2D one;	//!< Variablen - Texturplatzhalter
	vlgTextureMap2D two;	//!< Variablen - Texturplatzhalter
	vlgTextureMap2D three;	//!< Variablen - Texturplatzhalter
	vlgTextureMap2D four;	//!< Variablen - Texturplatzhalter
	vlgTextureMap2D five;	//!< Variablen - Texturplatzhalter
	vlgTextureMap2D six;	//!< Variablen - Texturplatzhalter
	
	

	//! Funktion zum füllen der Texture Map
	/*!
		* Die fillTextureList-Funktion der Wall fügt der \a textureMaps die
		* einzelnen Texturen(Bitmaps) für den Hintergrund hinzu.
		*
	*/
	void fillTextureListWall(void);

	//! Funktion zum bestimmen der Texturen - Namen, Adresse der Bitmaps
	/*!
		* Die fillNameList-Funktion der Wall liest die Bitmapnamen und Speicherorte
		* in \a textureNames ein.
	*/
	void fillNameListWall(void);

	//! Funktion die nächste Textur zu wählen
	/*!
		* Die nextTexture-Funktion schaltet den \a backgroundIndex um eins weiter.
		* Ist das Ende des Arrayindex bereits erreicht, wird backgroundIndex wieder
		* auf den kleinsten Arrayindex gesetzt. Anschließend wird die dem backgroundIndex
		* entsprechende Textur an den Hintergrund gebunden.
		*
		* \sa previousTexture()
	*/
	void nextTexture(void);

	//! Funktion die vorherige Textur zu wählen
	/*!
		* Die previousTexture-Funktion schaltet den \a backgroundIndex um eins zurück.
		* Ist der Anfang des Arrayindex bereits erreicht, wird backgroundIndex wieder
		* auf den letzten Arrayindex gesetzt. Anschließend wird die dem backgroundIndex
		* entsprechende Textur an den Hintergrund gebunden.
		*
		* \sa nextTexture()
	*/
	void previousTexture(void);

	//! get-Funktion x-Werte
	float getX(void);

	//! get-Funktion y-Werte
	float getY(void);

	//! set-Funktion x-Werte
	void setX(float x);

	//! set-Funktion y-Werte
	void setY(float y);

private:
	
	short status;	//!< Variable - Rückgabewerte des Erfolgsstatus beim Laden der Bitmaps
	int anzahlTexturen;		//!< Variable - Anzahl der Texturen	
	int index;		//!< Variable - Aktuell ausgewählte Textur
	float moveX, moveY;
};
#endif