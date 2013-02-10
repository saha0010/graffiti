#ifndef COLOR	
#define COLOR

#include <vlgSubject.h>
#include <vlgColor.h>
#include "vector"

class Color : public vlgSubject
{
public:
	//!Default Konstruktor
	/*
	 * Setzt den activeColorIndex auf 0
	 */
	Color(void);
	//!Konstruktor
	/*!
	 * Ruft Default Konstruktor auf und setzt Farbindex.
	 * \param int Farbindex
	 */
	Color(int farbIndex);
	
	//! Setter f�r activeColorIndex
	void setActiveColorByIndex(int i);

	//! Getter f�r activeColor
	vlgColor* getActiveColor(void);	

	//! Gibt die Gr��e von colorList zur�ck
	/*!
	 *	\return colorList.size()
	 */
	int getColorCount(void);

private:
	//!< aktive Farbe
	vlgColor *activeColor;	
	
	//!< Farbliste
	std::vector<vlgColor*> colorList;

};
#endif	COLOR
