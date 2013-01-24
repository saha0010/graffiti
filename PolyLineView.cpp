#include "PolyLineView.h"

#include <iostream>
#include <cmath>

#ifdef _WIN32
// Für Windows
#include <windows.h>
#endif
#include <GL/gl.h>

//!Konstruktor
PolyLineView::PolyLineView(std::vector<Line> &l) : line(l)
{
	//std::cout << "PolyLineView(vector<PolyLine> &l)" << std::endl;
	for(int i = 0; i<line.size();i++)
	{
		line.at(i).attach(this);
	}
}


bool PolyLineView::update(const vlgSubject &changedSubject)
{

	return true;
}

//!Grafische Ausgabe wird implzit in Graffiti::display() aufgerufen
	/*!Ausgabe für alle PolyLines die sich in vector lineList befinden */
void PolyLineView::draw(void)
{
glPolygonMode(GL_FRONT, GL_FILL);

	for(int i = 0;i<line.size();i++)
	{
		if (i == 0) 
			{zE=2;} 
		else 
		{
			zE= (float) (line.at(i).getMyUndoSizeZ()*0.02f);
		}				

		glColor3f(line.at(i).getActiveColor()->getRed(),
		  line.at(i).getActiveColor()->getGreen(), 
		  line.at(i).getActiveColor()->getBlue());
glBegin(GL_LINE_STRIP);
		for(int j = 0; j< line.at(i).myX.size();j++)
		{
			glVertex3f(line.at(i).myX.at(j),
						line.at(i).myY.at(j),		
						zE);
		}
		glEnd();
	}
			
}

