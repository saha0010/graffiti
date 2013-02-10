#ifndef SHAPE	
#define SHAPE

#include "Color.h"

//! Eine Klasse von der geometrische Figuren abgeleiet werden
class Shape : public Color
{
public:
	//! Getter Methode für myX
	float getX(void);
	//! Getter Methode für myY
	float getY(void);
	//! Getter Methode für myZ
	float getZ(void);
	//! Getter Methode für filled
	bool getFilled(void);

	//! Setter Methode für myX
	void setX(float x);
	//! Setter Methode für myY
	void setY(float y);
	//! Setter Methode für myZ
	void setZ(float z);
	//! Setter Methode für filled
	void setFilled(bool fill);

protected :
	float myX;	//!< Variable für X-Koordinate, des Mittelpunktes eines ShapeObjektes
	float myY;	//!< Variable für Y>Koordinate, des Mittelpunktes eines ShapeObjektes
	float myZ;	/*!< Variable für Z-Wert. 
				 *	Dieser entspricht der Entfernung zur Kinect und ist für eine Saklierung
				 *  des Shap-Opjektes gedacht.
				 */

	bool filled;	/*!< Variable um zu entscheiden ob ein Shap-Objekt gefüllt oder ungefüllt ausgegeben werden soll
					 *	 Diese Funktionalität wurde noch nicht implentiert.
					 *	 Sollte dies implementiert werden so müsste dies in der draw-Methode der jeweiligen View gemacht
					 *	 werden.
					 */
};

#endif SHAPE