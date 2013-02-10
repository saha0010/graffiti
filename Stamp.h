#ifndef STAMP
#define STAMP

#include <vector>
#include <string>
#include <iostream>
#include "vlgTextureMap2D.h"
#include "Rectangle.h"

//! Modell Klasse f�r Stempel
class Stamp : public Rectangle
{
public:
	//! Konstruktor
	/*!
	 * \param float x, float y, float z
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

	//! Getter Methode f�r stampIndex
	int getStampIndex(void);

	//! Getter Methode f�r stampNames
	vector<string> getStampNames(void);

	//! Getter Methode f�r stampMaps
	vector<vlgTextureMap2D> getStampMaps(void);
	
	//! Getter Methode f�r staNames
	GLuint* getStaNames(void);
private:
	
	short status;	//!< Variable f�r die Speicherung des Status w�hrend des Texturebindings	
	int stampIndex;	//!< Variable f�r den Index des Listenplatzes der gew�hlten Texture	
	int anzahlStamps;	//!< Variable f�r die Anzahl der Texturen; stampMaps.size()

	GLuint staNames[1];					//!< Array zum Halten der Texturen
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