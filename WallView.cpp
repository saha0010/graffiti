#include "WallView.h"

WallView::WallView(void)
{
	std::cout<<"WallView()"<<std::endl;
}

WallView::WallView(Wall &w)
{
	std::cout<<"WallView - Kopierkonsturktor"<<std::endl;
	*wall = w;
}

WallView::WallView(Wall *w)
{
	std::cout<<"WallView(Wall *w)"<<std::endl;
	wall = w;
}

WallView& WallView::operator=(WallView& w)
{
	std::cout<<"WallView Kopierzuweisungskonstruktor"<<std::endl;
	wall = w.wall;
	return *this;
}

bool WallView::update(const vlgSubject &changedSubject)
{
	std::cout<<"WallView - Update()"<<std::endl;
	return true;
}

void WallView::draw(void)
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, wall->texNames[wall->backgroundIndex]);	
		glBegin(GL_QUADS);	
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-4.0f, -3.0f,-5.0f);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(4.0f, -3.0f,-5.0f);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(4.0f, 3.0f,-5.0f);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-4.0f, 3.0f,-5.0f);
		glEnd();
	glDisable(GL_TEXTURE_2D);

/*
//White Background
glPolygonMode(GL_FRONT,GL_FILL);
glBegin(GL_QUADS);
glColor3f(1.0f,1.0f,1.0f);
	glVertex3f(-4.0f, -3.0f,-5.0f);
	glVertex3f(4.0f, -3.0f,-5.0f);
	glVertex3f(4.0f, 3.0f,-5.0f);
	glVertex3f(-4.0f, 3.0f,-5.0f);
glEnd();	
*/
	
	if (wall->showDataReceived)
	{
	dataReceivedCircle();
	visionMode();
	}
}

//! Visuelle Wiedergabe des Tracker Signals
void WallView::dataReceivedCircle(void)
{ 
// Source Prof.Brill Computergrafik Beispiel "TrafficLight"
	float h = 2.0f*static_cast<float>(M_PI)/static_cast<float>(32);
	glPolygonMode(GL_FRONT, GL_FILL);
	dataReceived(wall->received);

	// Kreis ausgeben
	glBegin(GL_TRIANGLE_FAN);
	    for (int i=0; i<32; i++)
			glVertex2f(3.75f+0.1f*cos(static_cast<float>(i*h)), 
			           -4.25f + 1.5f + 0.1f*sin(static_cast<float>(i*h)));
	glEnd();
}

// Tracker Daten empfangen
void WallView::dataReceived(bool data)
{
	if (data)
		glColor3f(0.0f, 1.0f, 0.0f);
	else
		glColor3f(1.0f, 0.0f, 0.0f);
}

void WallView::visionMode(void)
{
	float h = 2.0f*static_cast<float>(M_PI)/static_cast<float>(18);
	glBegin(GL_POLYGON);
	glEnable(GL_LINE_SMOOTH);
	glColor3f(((float)wall->getActiveColor()->getRed())/255,
		      ((float)wall->getActiveColor()->getGreen())/255,
			  ((float)wall->getActiveColor()->getBlue())/255);
			
		for(int i = 0; i<360;i++)
			glVertex3f(wall->getX() + 0.075f*cos(static_cast<float>(i*h)),
					   wall->getY() + 0.075f*sin(static_cast<float>(i*h)),  
					   2.0f);	
		glEnd();
}

