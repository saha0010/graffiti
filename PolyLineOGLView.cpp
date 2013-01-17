#include "PolyLineOGLView.h"

#include <iostream>
#include <cmath>

#ifdef _WIN32
// Für Windows
#include <windows.h>
#endif
#include <GL/gl.h>

//!Konstruktor
PolyLineOGLView::PolyLineOGLView(std::vector<Line> &l) : lines(l)
{
	//std::cout << "PolyLineOGLView(vector<PolyLine> &l)" << std::endl;
	for(int i = 0; i<lines.size();i++)
	{
		lines.at(i).attach(this);
	}
}


bool PolyLineOGLView::update(const vlgSubject &changedSubject)
{

	return true;
}

//!Grafische Ausgabe wird implzit in Graffiti::display() aufgerufen
	/*!Ausgabe für alle PolyLines die sich in vector lineList befinden */
void PolyLineOGLView::draw(void)
{	
			float h =  2.0f*static_cast<float>(M_PI)/static_cast<float>(32 );
        float zd = -0.1f, deltaZ = 0.1f;
		for(int i =(int)lines.size();i<=0 ;i--)
			//for(int i= 0; i<(int)lines.size(); i++)
	
		{	

				//glBegin(GL_LINE_STRIP);
			glColor3f(lines.at(i).getActiveColor()->getRed(),
			  lines.at(i).getActiveColor()->getGreen(), 
			  lines.at(i).getActiveColor()->getBlue());
/*
			for(int j = 0;j<lines.at(i).myX.size();j++)
			{
				glVertex2f(lines.at(i).myX.at(j) ,lines.at(i).myY.at(j)); 
			}	
*/	
		glPolygonMode(GL_FRONT, GL_FILL);
	
		for(int j = 0; j<lines.at(i).myX.size();j++)
		{		
			glBegin(GL_TRIANGLE_STRIP);
	    for (int k=0; k<32; k++)
			glVertex3f(lines.at(i).myX.at(j) + 0.15f*cos(static_cast<float>(k*h)), 
			           lines.at(i).myY.at(j) + 0.15f*sin(static_cast<float>(k*h)),
					   zd);
					   //(float)(i*10));
			
		}

        glEnd();

		
		zd += deltaZ;
		std::cout << "z-Wert ist: " << zd << std::endl;
		}	
			
}

