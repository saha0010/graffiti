#include "StampView.h"

StampView::StampView(std::vector<Stamp> &s):stamps(s)
{
	std::cout << "StampView(std::vector<Stamp> &s)" << std::endl;
	//attach() wird impliziet aufgerufen
}

void StampView::draw(void)
{
	//for(int i=0;i<stamps.size();i++)
	for(int i = (int)stamps.size()-1; i>=0;i--)
	{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, stamps.at(i).getStaNames()[stamps.at(i).getStampIndex()]);	
		glBegin(GL_QUADS);	
			glTexCoord2f(0.0f, 0.0f); 
			glVertex3f(stamps[i].getX()-stamps[i].getWidth(), stamps[i].getY()-stamps[i].getHeight(), stamps[i].getZ()*0.02f);

			glTexCoord2f(1.0f, 0.0f); 
			glVertex3f(stamps[i].getX()+stamps[i].getWidth(), stamps[i].getY()-stamps[i].getHeight(), stamps[i].getZ()*0.02f);

			glTexCoord2f(1.0f, 1.0f); 
			glVertex3f(stamps[i].getX()+stamps[i].getWidth(), stamps[i].getY()+stamps[i].getHeight(), stamps[i].getZ()*0.02f);

			glTexCoord2f(0.0f, 1.0f); 
			glVertex3f(stamps[i].getX()-stamps[i].getWidth(), stamps[i].getY()+stamps[i].getHeight(), stamps[i].getZ()*0.02f);

		glEnd();
	glDisable(GL_TEXTURE_2D);
	}
}


bool StampView::update(const vlgSubject &changedSubject)
{std::cout<<"StampView::Update()"<<std::endl;

return true;
}
