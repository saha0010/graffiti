#include "TriangleView.h"

#include <cmath>

#ifdef _WIN32
// Für Windows
#include <windows.h>
#endif
#include <GL/gl.h>



TriangleView::TriangleView(std::vector<Triangle> &t):triangles(t)
{
	for(int i =0;i<triangles.size();i++)
	{
		triangles.at(i).attach(this);
	}

}


void TriangleView::draw(void)
{
	for(int j = (int)triangles.size()-1; j>=0;j--)
	{

		glPolygonMode(GL_FRONT, GL_FILL);	

		glColor3f(((float)triangles[j].getActiveColor()->getRed())/255,
				 ((float)triangles[j].getActiveColor()->getGreen())/255, 
				 ((float)triangles[j].getActiveColor()->getBlue())/255);

	// Do the Triangle!!
		glBegin(GL_TRIANGLE_STRIP);
		glVertex3f(triangles[j].getX(),
				   triangles[j].getY() + (triangles[j].getSize()),
				   triangles[j].getZ()*0.02f);

		glVertex3f(triangles[j].getX() + (triangles[j].getSize()),
				   triangles[j].getY() - (triangles[j].getSize()),
				   triangles[j].getZ()*0.02f);

		glVertex3f(triangles[j].getX() - (triangles[j].getSize()),
				   triangles[j].getY() - (triangles[j].getSize()),
				   triangles[j].getZ()*0.02f);

		glEnd();
	}
}

bool TriangleView::update(const vlgSubject &changedSubject)
{
	std::cout << "TriangleView::update(const vlgSubject &changedSubject)" << std::endl;
	return true;
}