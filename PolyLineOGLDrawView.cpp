#include "PolyLineOGLDrawView.h"

#include <iostream>
#include <cmath>

#ifdef _WIN32
// Für Windows
#include <windows.h>
#endif
#include <GL/gl.h>

PolyLineOGLDrawView::PolyLineOGLDrawView(std::vector<Line> &l) : line(l)
{
	//std::cout << "PolyLineOGLView(vector<PolyLine> &l)" << std::endl;
	for(int i = 0; i<line.size();i++)
	{
		line.at(i).attach(this);
	}
	
	
}

bool PolyLineOGLDrawView::update(const vlgSubject &changedSubject)
{
	std::cout << "Mach ich noch" << std::endl;
	return true;
}

//!Grafische Ausgabe wird implzit in Graffiti::display() aufgerufen
	//! Ausgabe der momentan gemalten Line 
void PolyLineOGLDrawView::draw(void)
{	float h =  2.0f*static_cast<float>(M_PI)/static_cast<float>(32);

	for(int i = 0;i<line.size();i++)
	//for (int i = (int)line.size()-1; i>=0; i--)
	{
		zd = (float) (line.at(i).getMyUndoSizeZ()*0.001f);	// z-Ebenen der Linien innerhalb der Linienliste
		//zdO = (float) (0.01f * line.size());				// z-E der aktuellen/ersten Linie in Abhängigkeit der Max-Anzahl
		zdO = (float) (0.01f * line.at(i).getMyUndoSizeZ());
		if ( i==0 ) {zE=zdO;} else {zE=zd;}					// Prüfe auf Listenposition 

			glColor3f(line.at(i).getActiveColor()->getRed(),
			  line.at(i).getActiveColor()->getGreen(), 
			  line.at(i).getActiveColor()->getBlue());

			glPolygonMode(GL_FRONT, GL_FILL);
			
		for(int j = 0; j< line.at(i).myX.size();j++)
		{
					
		glBegin(GL_TRIANGLE_FAN);
			for (int k=32; k>=0; k--){

		
				glVertex3f(line.at(i).myX.at(j) + (line.at(i).myZ.at(j))*cos(static_cast<float>(k*h)), // x-Wert
					line.at(i).myY.at(j) + (line.at(i).myZ.at(j))*sin(static_cast<float>(k*h)),		// y-Wert
					zE);																// z-Wert
					//(float)(i*0.01f));
					//2.0f);
				
			}
			glEnd();			
		}
			
		}	
}

