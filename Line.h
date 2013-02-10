#ifndef LINE
#define LINE

#include "Color.h"
#include "vector"

class Line : public Color
{
public:
	//!Default Konstruktor
	Line(void);

	//!
	Line(int i);

	std::vector<float> getMyX(void);
	std::vector<float> getMyY(void);
	std::vector<float> getMyZ(void); //new
	float getMyUndoSizeZ(void);
	

	//!Funktion um Inhalt von myX und myY zu löschen
	/*!
		* Die clear-Funktion löscht den Inhalt aus der 
		* myX- und myY-Liste.
	*/
	void clear(void);
	std::vector<float> myX;	//!< Liste um X-Werte zu speichern
	std::vector<float> myY;	//!< Liste um Y-Werte zu speichern
	std::vector<float> myZ; //!< Liste um Z-Werte zu speichern	/new
	float myUndoSizeZ;	//!< Hilfe zur Darstellung in der Z-Ebene //new

private:
	//std::vector<float> myX;	//!< Liste um X-Werte zu speichern
	//std::vector<float> myY;	//!< Liste um Y-Werte zu speichern
};
#endif 