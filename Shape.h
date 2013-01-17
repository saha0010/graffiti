#ifndef SHAPE	
#define SHAPE

#include "Color.h"

class Shape : public Color
{
public:
	 float getX(void);
	 float getY(void);
	 float getZ(void);
	 bool getFilled(void);

	 void setX(float x);
	 void setY(float y);
	 void setZ(float z);
	 void setFilled(bool fill);

protected :
	float myX;
	float myY;
	float myZ; //- Platzhalter sprühradius

	bool filled;
};

#endif SHAPE