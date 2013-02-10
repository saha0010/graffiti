#ifndef LINE
#define LINE

#include "Color.h"
#include <vector>

//! Modell Klasse f�r eine Linie
class Line : public Color
{
public:
	//!Default Konstruktor
	/*!
	 * Setzt activeColorIndex auf 0
	 */
	Line(void);

	//!Konstruktor
	/*!
	 * Ruft die Funktion setActiveColorIndex mit i als Parameter auf 
	 * \param int i als Farbindex
	 */
	Line(int i);

	/*
	 * Getter Methoden f�t public Member, da diese Member in einer fr�heren Version einmal privat waren.
	 */
	//!Getter Methode f�t myX
	std::vector<float> getMyX(void);
	//!Getter Methode f�t myY
	std::vector<float> getMyY(void);
	//!Getter Methode f�t myZ
	std::vector<float> getMyZ(void);

	//!Getter Methode f�r myUndoSizeZ
	float getMyUndoSizeZ(void);
	
	//!Funktion um Inhalt von myX und myY zu l�schen
	/*!
		* Die clear-Funktion l�scht den Inhalt aus  
		* myX, myY und myZ.
	*/
	void clear(void);
	
	/*
	 * Member die eigentlich privat sein sollten sind public, da es ansonsten zu Fehler beim zugrif in der handleTracker
	 * Methode kam.
	 */
	std::vector<float> myX;	//!< Liste um X-Werte zu speichern
	std::vector<float> myY;	//!< Liste um Y-Werte zu speichern
	std::vector<float> myZ; //!< Liste um Z-Werte zu speichern	
	float myUndoSizeZ;	//!< Hilfe zur Darstellung in der Z-Ebene 
private:

};
#endif 