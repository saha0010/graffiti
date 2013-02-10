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
	
	//! Setter für activeColorIndex
	void setActiveColorByIndex(int i);

	//! Getter für activeColor
	vlgColor* getActiveColor(void);	

	//! Gibt die Größe von colorList zurück
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
