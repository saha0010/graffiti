#ifndef COLOR	
#define COLOR

#include <vlgSubject.h>
#include <vlgColor.h>

class Color : public vlgSubject
{
public:
	 Color(void);
	 Color(int i);
	
	void setActiveColorByIndex(int i);
	void setActiveColor(vlgColor *color);
	vlgColor* getActiveColor(void);	

private:
	vlgColor *colorList[6];	//!< Farbliste
	vlgColor *activeColor;	//!< aktive Farbe
	
};
#endif	COLOR
