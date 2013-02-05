#include "CircleLineView.h"

#include <iostream>
#include <cmath>

#ifdef _WIN32
// Für Windows
#include <windows.h>
#endif
#include <GL/gl.h>

CircleLineView::CircleLineView(std::vector<Line> &l) : line(l), shader(vlgShaderHandler::Instance()), errorCode(0), vertexShader("yellow.vsh")
{
	//std::cout << "PolyLineView(vector<PolyLine> &l)" << std::endl;
	for(int i = 0; i<line.size();i++)
	{
		line.at(i).attach(this);
	}

}

 // Initialisierung des GLSL Shader-Handlers
void CircleLineView::initShader(void)
{
	    // Ausgaben des Shader-Compilers und Linkers auf die Konsole
	    shader->verboseOn();
	    shader->setVertexShaderSource(vertexShader);
	    shader->vertexShaderOn();
	    errorCode = shader->installProgram();
	    if (errorCode != 0)
			std::cerr << "Fehler beim Installieren des Shader Programs" <<std::endl; 
}

bool CircleLineView::update(const vlgSubject &changedSubject)
{
	return true;
}

//!Grafische Ausgabe wird implzit in Graffiti::display() aufgerufen
	//! Ausgabe der momentan gemalten Line 
void CircleLineView::draw(void)
{	
	float h =  2.0f*static_cast<float>(M_PI)/static_cast<float>(32);
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Shader-Programm aktivieren
    if (errorCode == 0)
             shader->programOn(); 
	for(int i = 0;i<line.size();i++)
	{
		if (i == 0) 
			{zE=2;} 
		else 
		{
			zE= (float) (line.at(i).getMyUndoSizeZ()*0.02f);
		}		

		
			glColor3f(((float)line.at(i).getActiveColor()->getRed())/255,
					  ((float)line.at(i).getActiveColor()->getGreen())/255, 
					  ((float)line.at(i).getActiveColor()->getBlue())/255);
			
			
	

		for(int j = 0; j< line.at(i).myX.size();j++)
		{
		glPolygonMode(GL_FRONT, GL_FILL);	
		glBegin(GL_TRIANGLE_FAN);
			for (int k=32; k>=0; k--) {
		
				glVertex3f(line.at(i).myX.at(j) + (line.at(i).myZ.at(j)*-0.1f)*cos(static_cast<float>(k*h)), // x-Wert
					line.at(i).myY.at(j) + (line.at(i).myZ.at(j)*-0.1f)*sin(static_cast<float>(k*h)),		// y-Wert
					zE);																// z-Wert
				
			}
			glEnd();	

		}
			
		}	
    shader->programOff();
}


