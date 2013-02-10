#include "CircleLineView.h"

#include <iostream>
#include <cmath>

#ifdef _WIN32
// Für Windows
#include <windows.h>
#endif
#include <GL/gl.h>

CircleLineView::CircleLineView(std::vector<Line> &l) : line(l), shader(vlgShaderHandler::Instance()), errorCode(0), vertexShader("yellow.vsh"),blending(false)
{
	// attach wird implizit aufgerufen
}

 // Initialisierung des GLSL Shader-Handlers
void CircleLineView::initShader(void)
{
	    // Ausgaben des Shader-Compilers und Linkers auf die Konsole
	    shader->verboseOn();
		std::cout<<glGetString(GL_SHADING_LANGUAGE_VERSION)<<std::endl;
	    shader->setFragmentShaderSource(vertexShader);
		shader->fragmentShaderOn();
	    errorCode = shader->installProgram();
		
	    if (errorCode != 0)
			std::cerr << "Fehler beim Installieren des Shader Programs" <<std::endl; 

		// Uniform-Variable verbinden
		if (errorCode == 0)
		{
			uniform = new vlgShaderUniform(shader->getProgram(), "color");
			shader->programOn();
			uniform->set("color", 1.0f, 0.0f, 0.0f);
		}
}

bool CircleLineView::update(const vlgSubject &changedSubject)
{
	return true;
}

// Ausgabe der momentan gemalten Line 
void CircleLineView::draw(void)
{	
	float h =  2.0f*static_cast<float>(M_PI)/static_cast<float>(32);
	if(blending)
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

    // Shader-Programm aktivieren
	if (errorCode == 0)
             shader->programOn();
	//Schleife durch alle Linien
	for(int i = 0;i<line.size();i++)
	{
		if (i == 0)
			zE=2;
		else 
			zE= (float) (line.at(i).getMyUndoSizeZ()*0.002f);// 0.002 da bei 0.001 Fehler enstanden sind
		
		//Shader die Farbe übergeben
		if (errorCode == 0)
			{
			uniform->set("color", (float)line.at(i).getActiveColor()->getRed()/255,
								  (float)line.at(i).getActiveColor()->getGreen()/255,
								  (float)line.at(i).getActiveColor()->getBlue()/255);
			}
		//Schleife durch alle Punkte einer Linie
		for(int j = 0; j< line.at(i).myX.size();j++)
		{
			glPolygonMode(GL_FRONT, GL_FILL);	
			glBegin(GL_TRIANGLE_FAN);
			//Schleife um einen Kreis für einen bestimmten Punkt zu malen
			for (int k=32; k>=0; k--) 
			{
				glVertex3f(line.at(i).myX.at(j) + (line.at(i).myZ.at(j)*-0.1f)*cos(static_cast<float>(k*h)),
					line.at(i).myY.at(j) + (line.at(i).myZ.at(j)*-0.1f)*sin(static_cast<float>(k*h)),		
					zE);																				
			}
			glEnd();	
		}			
	}	
    shader->programOff();
}

void CircleLineView::setBlending(bool b)
{ blending = b;}
bool CircleLineView::getBlending(void)
{return blending;}
