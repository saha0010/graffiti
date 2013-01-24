#include "CircleLineView.h"

#include <iostream>
#include <cmath>

#ifdef _WIN32
// Für Windows
#include <windows.h>
#endif
#include <GL/gl.h>

CircleLineView::CircleLineView(std::vector<Line> &l) : line(l)
{
	//std::cout << "PolyLineView(vector<PolyLine> &l)" << std::endl;
	for(int i = 0; i<line.size();i++)
	{
		line.at(i).attach(this);
	}
	
	
}

bool CircleLineView::update(const vlgSubject &changedSubject)
{
	std::cout << "Mach ich noch" << std::endl;
	return true;
}

//!Grafische Ausgabe wird implzit in Graffiti::display() aufgerufen
	//! Ausgabe der momentan gemalten Line 
void CircleLineView::draw(void)
{	float h =  2.0f*static_cast<float>(M_PI)/static_cast<float>(32);
//	glEnable(GL_BLEND);
//	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	for(int i = 0;i<line.size();i++)
	{
		//zdO = (float) (0.01f * line.size());				// z-E der aktuellen/ersten Linie in Abhängigkeit der Max-
		if (i == 0) 
			{zE=2;} 
		else 
		{
			zE= (float) (line.at(i).getMyUndoSizeZ()*0.02f);
		}		

			glColor3f(line.at(i).getActiveColor()->getRed(),
			  line.at(i).getActiveColor()->getGreen(), 
			  line.at(i).getActiveColor()->getBlue());

			
		for(int j = 0; j< line.at(i).myX.size();j++)
		{
		glPolygonMode(GL_FRONT, GL_FILL);		
		glBegin(GL_TRIANGLE_FAN);
			for (int k=32; k>=0; k--){

		
				glVertex3f(line.at(i).myX.at(j) + (line.at(i).myZ.at(j)*-0.1f)*cos(static_cast<float>(k*h)), // x-Wert
					line.at(i).myY.at(j) + (line.at(i).myZ.at(j)*-0.1f)*sin(static_cast<float>(k*h)),		// y-Wert
					zE);																// z-Wert
				
			}
			glEnd();			
		}
			
		}	
}

