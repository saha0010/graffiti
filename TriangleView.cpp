#include "TriangleView.h"

#include <cmath>

#ifdef _WIN32
// Für Windows
#include <windows.h>
#endif
#include <GL/gl.h>

TriangleView::TriangleView(std::vector<Triangle> &t):triangles(t)
{
}

void TriangleView::draw(void)
{
	//Schleife durch die Dreiecksliste
	for(int j = (int)triangles.size()-1; j>=0;j--)
	{
		glPolygonMode(GL_FRONT, GL_FILL);	
		glColor3f(((float)triangles[j].getActiveColor()->getRed())/255,
				 ((float)triangles[j].getActiveColor()->getGreen())/255, 
				 ((float)triangles[j].getActiveColor()->getBlue())/255);

		glBegin(GL_TRIANGLE_STRIP);
		glVertex3f(triangles[j].getX(),
				   triangles[j].getY() + (triangles[j].getSize()),
				   triangles[j].getZ()*0.002f);

		glVertex3f(triangles[j].getX() + (triangles[j].getSize()),
				   triangles[j].getY() - (triangles[j].getSize()),
				   triangles[j].getZ()*0.002f);

		glVertex3f(triangles[j].getX() - (triangles[j].getSize()),
				   triangles[j].getY() - (triangles[j].getSize()),
				   triangles[j].getZ()*0.002f);
		glEnd();
	}
}

bool TriangleView::update(const vlgSubject &changedSubject)
{
	return true;
}