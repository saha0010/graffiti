#ifndef STAMP
#define STAMP

#include <vector>
#include <string>
#include <iostream>
#include "vlgTextureMap2D.h"
#include "Rectangle.h"

//! Klasse zum erstellen der Bitmaps - Texture Mapping
class Stamp : public Rectangle
{
public:
	//!OpenGL Initialisierung
	/*!
		* Die aktuelle Postion wird �bermittelt an jener das
		* Rechteck mit Texture bzw. das Bitmap angeh�ngt werden
		* soll.
	*/
	Stamp(float x=0, float y=0, float z=0);
	
	//! Funktion das n�chste Bitmap zu w�hlen
	/*!
		* Die nextStamp-Funktion schaltet den \a stampIndex um eins weiter.
		* Ist das Ende des Arrayindex bereits erreicht, wird stampIndex wieder
		* auf den kleinsten Arrayindex gesetzt. Anschlie�end wird die dem stampIndex
		* entsprechende Textur an das Rechteck gebunden.
	*/
	void nextStamp(void);

	short getStatus(void);
	int getAnzahlStamps(void);
	int getStampIndex(void);
	vector<string> getStampNames(void);
	vector<vlgTextureMap2D> getStampMaps(void);
	GLuint* getStaNames(void);
private:
	
	short status;		
	int stampIndex;		
	int anzahlStamps;	

	GLuint staNames[1];	//!< Array zum Halten der Texturen
	vector<vlgTextureMap2D> stampMaps;	//!< Liste f�r zweidimensionale Texturen
	vector<string> stampNames;	//!< Liste der Texturnamen
	vlgTextureMap2D one;		//!< Variablen - Texturplatzhalter

	//! Funktion zum f�llen der Texture Map
	/*!
		* Die fillTextureList-Funktion der Stamp f�gt der \a textureMaps die
		* einzelnen Texturen(Bitmaps) f�r den Hintergrund hinzu.
	*/
	void fillTextureListStamp(void);

	//! Funktion zum bestimmen der Texturen - Namen, Adresse der Bitmaps
	/*!
		* Die fillNameList-Funktion der Stamp liest die Bitmapnamen und Speicherorte
		* in \a textureNames ein.
	*/
	void fillNameListStamp(void);

	//! Funktion zum laden der Texturen
	/*!
		* Die createTextureMap-Funktion schaltet die 2D-Texturen frei und
		* l�dt die Bitmaps als Texturen ein. Danach werden die 
		* 2D-Texturen wieder ausgeschaltet um kein Fehlverhalten
		* mit glColor hervorzurufen.
	*/
	void createTextureMap(void);

};
#endif