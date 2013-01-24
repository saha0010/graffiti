#include "CircleView.h"

#include <cmath>

#ifdef _WIN32
// Für Windows
#include <windows.h>
#endif
#include <GL/gl.h>



CircleView::CircleView(std::vector<Circle> &c):circles(c),n(32)
{
	//std::cout << "CircleView(std::vector<Circle> &c)" << std::endl;
	h =  2.0f*static_cast<float>(M_PI)/static_cast<float>(n);
	for(int i =0;i<circles.size();i++)
	{
		circles.at(i).attach(this);
	}

}


void CircleView::draw(void)
{// Source Prof.Brill Computergrafik Beispiel "TrafficLight"	
	for(int j = (int)circles.size()-1; j>=0;j--)
	{
		
		if(circles[j].getFilled()==true)
			glPolygonMode(GL_FRONT, GL_FILL);
		else
			glPolygonMode(GL_FRONT, GL_LINE);

		glColor3f(circles[j].getActiveColor()->getRed(),
				  circles[j].getActiveColor()->getGreen(),
				  circles[j].getActiveColor()->getBlue()
				  );

		glBegin(GL_TRIANGLE_FAN);
	    for (int i=0; i<n; i++)	
		glVertex3f(circles[j].getX() + circles[j].getRadius()*cos(static_cast<float>(i*h)), 
			       circles[j].getY() + circles[j].getRadius()*sin(static_cast<float>(i*h)),
				   circles[j].getZ()*0.001f);
		glEnd();
	}
}

bool CircleView::update(const vlgSubject &changedSubject)
{
	std::cout << "CircleView::update(const vlgSubject &changedSubject)" << std::endl;
	return true;
}