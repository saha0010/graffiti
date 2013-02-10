#ifndef STAMP
#define STAMP

#include <vector>
#include <string>
#include <iostream>
#include "vlgTextureMap2D.h"
#include "Rectangle.h"

//! Modell Klasse für Stempel
class Stamp : public Rectangle
{
public:
	//! Konstruktor
	/*!
	 * \param float x, float y, float z
	 */
	Stamp(float x=0, float y=0, float z=0);
	
	//! Funktion das nächste Bitmap zu wählen
	/*!
		* Die nextStamp-Funktion schaltet den \a stampIndex um eins weiter.
		* Ist das Ende des Arrayindex bereits erreicht, wird stampIndex wieder
		* auf den kleinsten Arrayindex gesetzt. Anschließend wird die dem stampIndex
		* entsprechende Textur an das Rechteck gebunden.
	*/
	void nextStamp(void);

	//! Getter Methode für stampIndex
	int getStampIndex(void);

	//! Getter Methode für stampNames
	vector<string> getStampNames(void);

	//! Getter Methode für stampMaps
	vector<vlgTextureMap2D> getStampMaps(void);
	
	//! Getter Methode für staNames
	GLuint* getStaNames(void);
private:
	
	short status;	//!< Variable für die Speicherung des Status während des Texturebindings	
	int stampIndex;	//!< Variable für den Index des Listenplatzes der gewählten Texture	
	int anzahlStamps;	//!< Variable für die Anzahl der Texturen; stampMaps.size()

	GLuint staNames[1];					//!< Array zum Halten der Texturen
	vector<vlgTextureMap2D> stampMaps;	//!< Liste für zweidimensionale Texturen
	vector<string> stampNames;	//!< Liste der Texturnamen
	vlgTextureMap2D one;		//!< Variablen - Texturplatzhalter

	//! Funktion zum füllen der Texture Map
	/*!
		* Die fillTextureList-Funktion der Stamp fügt der \a textureMaps die
		* einzelnen Texturen(Bitmaps) für den Hintergrund hinzu.
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
		* lädt die Bitmaps als Texturen ein. Danach werden die 
		* 2D-Texturen wieder ausgeschaltet um kein Fehlverhalten
		* mit glColor hervorzurufen.
	*/
	void createTextureMap(void);

};
#endif