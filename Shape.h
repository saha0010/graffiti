#ifndef SHAPE	
#define SHAPE

#include "Color.h"

//! Eine Klasse von der geometrische Figuren abgeleiet werden
class Shape : public Color
{
public:
	//! Getter Methode f�r myX
	float getX(void);
	//! Getter Methode f�r myY
	float getY(void);
	//! Getter Methode f�r myZ
	float getZ(void);
	//! Getter Methode f�r filled
	bool getFilled(void);

	//! Setter Methode f�r myX
	void setX(float x);
	//! Setter Methode f�r myY
	void setY(float y);
	//! Setter Methode f�r myZ
	void setZ(float z);
	//! Setter Methode f�r filled
	void setFilled(bool fill);

protected :
	float myX;	//!< Variable f�r X-Koordinate, des Mittelpunktes eines ShapeObjektes
	float myY;	//!< Variable f�r Y>Koordinate, des Mittelpunktes eines ShapeObjektes
	float myZ;	/*!< Variable f�r Z-Wert. 
				 *	Dieser entspricht der Entfernung zur Kinect und ist f�r eine Saklierung
				 *  des Shap-Opjektes gedacht.
				 */

	bool filled;	/*!< Variable um zu entscheiden ob ein Shap-Objekt gef�llt oder ungef�llt ausgegeben werden soll
					 *	 Diese Funktionalit�t wurde noch nicht implentiert.
					 *	 Sollte dies implementiert werden so m�sste dies in der draw-Methode der jeweiligen View gemacht
					 *	 werden.
					 */
};

#endif SHAPE