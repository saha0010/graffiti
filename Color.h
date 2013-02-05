#ifndef COLOR	
#define COLOR

#include <vlgSubject.h>
#include <vlgColor.h>
#include "vector"

class Color : public vlgSubject
{
public:
	 Color(void);
	 Color(int i);
	
	void setActiveColorByIndex(int i);
	void setActiveColor(vlgColor *color);
	vlgColor* getActiveColor(void);	

	int getColorCount(void);

private:
	//!< aktive Farbe
	vlgColor *activeColor;	
	
	//!< Farbliste
	std::vector<vlgColor*> colorList;

};
#endif	COLOR
